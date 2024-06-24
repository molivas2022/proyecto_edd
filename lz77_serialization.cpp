#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "lz77_compression.h"

using namespace std; /* >.< */

void compress_file(const char *input_filename, const char *output_filename, int MAX_BUFFER = 16, size_t MEMORY_LIMIT = -1)
{
    ifstream input{input_filename}; /* leemos el archivo de texto */
    stringstream buffer; /* lo pasamos a un string */
    buffer << input.rdbuf();
    string str = buffer.str();

    auto code = compress_string(str, MAX_BUFFER, MEMORY_LIMIT); /* comprimimos el string */

    ofstream output{output_filename, ios::binary};
    for (int i = 0; i < code.size(); i++) /* escribimos cada par (posicion, largo) en el comprimido */
    {
        output.write((char *)&(code[i].first), sizeof(int));
        output.write((char *)&(code[i].second), sizeof(char));
    }

    input.close();
    output.close();
}

void decompress_file(const char *input_filename, const char *output_filename)
{
    ifstream input{input_filename, ios::binary}; /* abrimos el comprimido */
    if (!input.is_open())
    {
        /* debugging */ cout << "Oh oh!" << endl;
    }
    vector<pair<int, char>> vec;
    pair<int, char> value;
    while (true)
    {
        if (input.peek() != EOF) /* leemos cada par (posicion, largo) que esta en el comprimido */
        {
            input.read((char *)&value.first, sizeof(int));
            if (input.peek() != EOF)
            {
                input.read((char *)&value.second, sizeof(char));
                vec.push_back(value);
                continue;
            }
        }
        break;
    }

    auto decode = decompress_string(vec); /* con un vector de pares (posicion, largo) procedemos a descomprimir el texto */

    ofstream output{output_filename};
    output << decode; /* escribimos el texto descomprimido */

    input.close();
    output.close();
}
