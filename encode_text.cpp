#include "huffman_tree.h"
#include "huffman_coding.h"
#include "huffman_serialization.h"
#include <vector>
#include <fstream>
#include <iostream>

/* -- Funciones principales -- */
void encode_file(const char* input_filename, const char* output_filename);
void decode_file(const char* input_filename, const char* output_filename);

/* Durante ejecución, recibe como único parámetro un archivo de texto el cual codificar mediante árbol de Huffman
*
*   Compilación: 
*       g++ encode_text.cpp huffman_tree.cpp huffman_coding.cpp serialization.cpp -I headers/ -Wall -Wextra -o encode_text
*/
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Uso del programa: ./ejecutable <path de .txt a codificar>" << std::endl;
        exit(EXIT_FAILURE);
    }
    encode_file(argv[1], "compressed");
    decode_file("compressed", "decompressed.txt");

    return 0;
}

void encode_file(const char* input_filename, const char* output_filename) {
    std::fstream ifs(input_filename, std::fstream::in);

    auto code = Huffman::bit_encode(ifs);
    ifs.clear(); ifs.seekg(0, std::ios::beg);
    auto freq = Huffman::readFrequencies(ifs);  

    unsigned int code_length = code.first;
    unsigned char* encoded_bits = code.second;

    std::fstream ofs{output_filename, std::fstream::out | std::ios::binary};

    Huffman::IOS::serialize_freq(ofs, freq);
    Huffman::IOS::serialize_huffmancode(ofs, code_length, encoded_bits);

    ifs.close();
    ofs.close();
    delete encoded_bits;
}

void decode_file(const char* input_filename, const char* output_filename) {
    std::fstream ifs(input_filename, std::fstream::in | std::ios::binary);

    auto freq = Huffman::IOS::unserialize_freq(ifs);
    auto root = Huffman::createHuffmanTree(freq);
    auto code = Huffman::IOS::unserialize_huffmancode(ifs);

    auto decode = Huffman::bit_decode(code.second, code.first, root);

    std::fstream ofs{output_filename, std::fstream::out};
    ofs << decode;

    ifs.close();
    ofs.close();
    delete code.second;
}