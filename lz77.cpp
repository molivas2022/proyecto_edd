#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std; /* >.< */

/* -- Funciones principales -- */
/* Comprime un archivo input, creando un archivo output */
void compress_file(const char* input_filename, const char* output_filename);
/* Descomprime un archivo input, creando un archivo output */
void decompress_file(const char* input_filename, const char* output_filename);

/* -- Funciones auxiliares -- */
/* Comprime un string, la compresión corresponde a un vector de pares indice-longitud */
vector<pair<int, int>> compress_string(string input);
/* Devuelve un string descomprimido, dado su compresión como un vector de pares de indice-longitud */
string decompress_string(vector<pair<int, int>> input);
pair<string, int> longest_repeated_ocurrence(string search, string look);

/* -- Funciones de depuración -- */
/* Recorta el tamaño de un archivo de texto a un tamaño deseado (en bytes) */
void cut_file(int size, const char* input_filename, const char* output_filename);
/* Imprime los pares indice-longitud de una compresión */
void print_code(vector<pair<int, int>> code);

int main() {
    cut_file(1048576, "sample.txt", "sample_cut.txt"); /* 1048576 bytes = 1 mB */
    compress_file("sample_cut.txt", "sample_compressed.txt");
    decompress_file("sample_compressed.txt", "sample_decompressed.txt");
    /* Notar que sample_cut.txt y sample_decompressed.txt son identicos */
    return 0;
}

void cut_file(int size, const char* input_filename, const char* output_filename) {
    ifstream input{input_filename};
    ofstream output{output_filename};

    int i = 0;
    char c;
    while (i < size) {
        input.get(c);
        if (c == EOF) {break;}
        output << c;
        i += sizeof(c);
    }

    input.close();
    output.close();
}

void compress_file(const char* input_filename, const char* output_filename) {
    ifstream input{input_filename};
    stringstream buffer;
    buffer << input.rdbuf();
    string str = buffer.str();

    auto code = compress_string(str);

    /* debugging */
    int size = code.size() * 2 * sizeof(int);
    float in_kb = ((float)(size))/1000.0;
    cout << in_kb << " kB" << endl;

    ofstream output{output_filename, ios::binary};
    for (int i = 0; i < code.size(); i++) {
        output.write((char*)&(code[i].first), sizeof(int));
        output.write((char*)&(code[i].second), sizeof(int));
    }

    input.close();
    output.close();
}

void decompress_file(const char* input_filename, const char* output_filename) {
    ifstream input{input_filename, ios::binary};
    if (!input.is_open()) {
        /* debugging */ cout << "Oh oh!" << endl;
    }
    vector<pair<int, int>> vec;
    pair<int, int> value;
    while (true) {
        if (input.peek() != EOF) {
            input.read((char *)&value.first, sizeof(int));
            if (input.peek() != EOF) {
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

/* Fuente: https://en.wikipedia.org/wiki/LZ77_and_LZ78#LZ77 */
vector<pair<int, int>> compress_string(string input) {
    /* Variables */
    vector<pair<int, int>> output;
    string search_buffer;
    string lookup_buffer;
    pair<string, int> match;
    pair<int, int>value;

    /* First tuple out of main loop */
    value = make_pair(input[0], 0);
    output.push_back(value);

    /* Loop */
    int i = 1;
    while (i < input.length()) {
        search_buffer = input.substr(0, i-1);
        lookup_buffer = input.substr(i);
        match = longest_repeated_ocurrence(search_buffer, lookup_buffer);

        if (match.first.length() > 0) {
            value.first = match.second;
            value.second = match.first.length();

            i += match.first.length();
        }
        else {
            value.first = input[i];
            value.second = 0;

            i++;
        }

        output.push_back(value);

        /* debugging */
        cout << 100.0*((float)i)/((float)input.length()) << " %" << endl;
    }

    return output;
}

string decompress_string(vector<pair<int, int>> input) {
    string output;
    while (input.size() > 0) {
        auto code = input[0];
        input.erase(input.begin());
        
        if (code.second == 0) {
            output.append(string{(char)code.first});
        }
        else {
            output.append(output.substr(code.first, code.second));
        }
    }
    return output;
}

/* Fuente: ChatGPT señores */
std::pair<string, int> longest_repeated_ocurrence(string search, string look) {
    size_t len1 = search.length();
    size_t len2 = look.length();
    
    std::string longestMatch = "";
    int longestIndex;
    
    for (size_t i = 0; i < len1; ++i) {
        size_t matchLength = 0;
        
        for (size_t j = 0; (i + j) < len1 && j < len2; ++j) {
            if (search[i + j] == look[j]) {
                ++matchLength;
            } else {
                break;
            }
        }
        
        if (matchLength > longestMatch.length()) {
            longestMatch = search.substr(i, matchLength);
            longestIndex = i;
        }
    }
    
    return std::make_pair(longestMatch, longestIndex);
}

void print_code(vector<pair<int, int>> code) {
    for (int i = 0; i < code.size(); i++) {
        cout << '(';
        if (code[i].second == 0) {
            cout << (char)code[i].first;
        }
        else {
            cout << code[i].first;
        }
        cout << ", ";
        cout << code[i].second;
        cout << ")  ";
    }
    cout << endl;
}
