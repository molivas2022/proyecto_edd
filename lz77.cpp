#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "lz77.h"
#include "trie.h"
using namespace std; /* >.< */

void cut_file(int size, const char *input_filename, const char *output_filename)
{
    ifstream input{input_filename};
    ofstream output{output_filename};

    int i = 0;
    char c;
    while (i < size)
    {
        input.get(c);
        if (c == EOF)
        {
            break;
        }
        output << c;
        i += sizeof(c);
    }

    input.close();
    output.close();
}

/* Fuente: https://en.wikipedia.org/wiki/LZ77_and_LZ78#LZ77 */
vector<pair<int, int>> compress_string(string input)
{
    /* Variables */
    vector<pair<int, int>> output;
    Trie trie;
    int MAX_BUFFER = 255;
    int search_buffer_left = 0;
    // Esto esta dado por:
    // first: index
    // second: length
    pair<int, int> aux;

    /* Loop */
    int input_index = 0;
    while (input_index < input.length())
    {
        // Esto sirve para mantener siempre lo siguiente:

        if (input_index - search_buffer_left > 255)
        {
            search_buffer_left = input_index - MAX_BUFFER;
        }

        aux = trie.find_longest_match(input, input_index);
        int index = aux.first;
        int length = aux.second;

        if (length == 0)
        {
            output.emplace_back((int)input[input_index], 0);

            for (int i = search_buffer_left; i < input_index; i++)
            {
                trie.insert(input, i, input_index - i);
            }

            input_index++;
        }
        else
        {
            output.emplace_back(index, length);

            for (int i = search_buffer_left; i < input_index; i++)
            {
                trie.insert(input, i, input_index - i);
            }

            input_index += length;
        }

        // Insertamos las palabras desde el limite inferior, hasta el inferior

        /* debugging */
        cout
            << 100.0 * ((float)input_index) / ((float)input.length()) << " %" << endl;
    }

    return output;
}

string decompress_string(vector<pair<int, int>> input)
{
    string output;
    while (input.size() > 0)
    {
        auto code = input[0];
        input.erase(input.begin());

        if (code.second == 0)
        {
            output.append(string{(char)code.first});
        }
        else
        {
            if (output.length() >= code.first + code.second)
            {
                output.append(output.substr(code.first, code.second));
            }
            else
            {
                cout << "hubo un error con: (" << code.first << ", " << code.second << ")" << endl;
            }
        }
    }
    return output;
}

void compress_file(const char *input_filename, const char *output_filename)
{
    ifstream input{input_filename};
    stringstream buffer;
    buffer << input.rdbuf();
    string str = buffer.str();

    auto code = compress_string(str);

    /* debugging */
    int size = code.size() * (sizeof(int) + sizeof(int));
    float in_kb = ((float)(size)) / 1000.0;
    cout << in_kb << " kB" << endl;

    ofstream output{output_filename, ios::binary};
    for (int i = 0; i < code.size(); i++)
    {
        output.write((char *)&(code[i].first), sizeof(int));
        output.write((char *)&(code[i].second), sizeof(int));
    }

    input.close();
    output.close();
}

void decompress_file(const char *input_filename, const char *output_filename)
{
    ifstream input{input_filename, ios::binary};
    if (!input.is_open())
    {
        /* debugging */ cout << "Oh oh!" << endl;
    }
    vector<pair<int, int>> vec;
    pair<int, int> value;
    while (true)
    {
        if (input.peek() != EOF)
        {
            input.read((char *)&value.first, sizeof(int));
            if (input.peek() != EOF)
            {
                input.read((char *)&value.second, sizeof(int));
                vec.push_back(value);
                continue;
            }
        }
        break;
    }

    auto decode = decompress_string(vec);

    ofstream output{output_filename};
    output << decode;

    input.close();
    output.close();
}

void print_code(vector<pair<int, int>> code)
{
    for (int i = 0; i < code.size(); i++)
    {
        cout << "index: " << i << ", " << "par: ";
        cout << '(';
        if (code[i].second == 0)
        {
            cout << (char)code[i].first;
        }
        else
        {
            cout << code[i].first;
        }
        cout << ", ";
        cout << code[i].second;
        cout << ")  ";
        cout << endl;
    }
}

// Fuente: Chat GPT >.<
void compararArchivos(const std::string &archivo1, const std::string &archivo2)
{
    std::ifstream file1(archivo1);
    std::ifstream file2(archivo2);

    if (!file1.is_open() || !file2.is_open())
    {
        std::cerr << "Error al abrir los archivos." << std::endl;
        return;
    }

    std::string lineaArchivo1, lineaArchivo2;
    bool sonIguales = true;

    while (std::getline(file1, lineaArchivo1) && std::getline(file2, lineaArchivo2))
    {
        if (lineaArchivo1 != lineaArchivo2)
        {
            sonIguales = false;
            break;
        }
    }

    // Verificar si uno de los archivos tiene más líneas que el otro
    if (sonIguales)
    {
        if ((file1.eof() && !file2.eof()) || (!file1.eof() && file2.eof()))
        {
            sonIguales = false;
        }
    }

    if (sonIguales)
    {
        std::cout << "son iguales" << std::endl;
    }
    else
    {
        std::cout << "wuawuawuawuaaaaaaaaa" << std::endl;
    }

    file1.close();
    file2.close();
}
