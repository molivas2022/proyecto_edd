#include "huffman.h"
#include "file_operations.h"
#include <vector>
#include <fstream>
#include <iostream>

/* que vas a hacer al respecto martin? */
#include "serialization.cpp" 

using namespace std;

/* -- Funciones principales -- */
void encode_file(const char* input_filename, const char* output_filename);
void decode_file(const char* input_filename, const char* output_filename);

/* Durante ejecución, recibe como único parámetro un archivo de texto el cual codificar mediante árbol de Huffman
*/
int main(int argc, char** argv) {
    encode_file(argv[1], "compressed");

    return 0;
}

void encode_file(const char* input_filename, const char* output_filename) {
    std::fstream ifs(input_filename, std::fstream::in);

    HuffmanCoding hc;
    HuffmanFileHandler hfs;

    auto code = hc.bit_encode(ifs);
    ifs.clear(); ifs.seekg(0, std::ios::beg);
    auto freq = readFrequencies(ifs);  

    unsigned int code_length = code.first;
    unsigned char* encoded_bits = code.second;

    std::fstream ofs{output_filename, std::fstream::out | std::ios::binary};

    serialize_freq(ofs, freq);
    serialize_huffmancode(ofs, code_length, encoded_bits);

    ifs.close();
    ofs.close();
    delete encoded_bits;
}

void decode_file(const char* input_filename, const char* output_filename) {
    std::cout << "TO-DO >.<" << std::endl;
}