#include "huffman_serialization.h"
#include "huffman_coding.h"
#include "huffman_tree.h"

#include <iostream>
#include <fstream>
#include <unordered_map>

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
    delete[] encoded_bits;
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
    delete[] code.second;
}

void Huffman::IOS::serialize_huffmancode(std::fstream& output, const unsigned int& number_of_bits, unsigned char * code) {
    /* Escribimos el número de bits */
    output.write((char*)&number_of_bits, sizeof(unsigned int));

    /* Calculamos el tamaño de la secuencia */
    unsigned int len;
    if (number_of_bits % 8 == 0) {
        len =  number_of_bits/8;
    }
    else {
        len =  (number_of_bits/8) + 1;
    }

    /* Escribimos la secuencia */
    output.write((char *)code, sizeof(unsigned char)*len);
}

std::pair<unsigned int, unsigned char*> Huffman::IOS::unserialize_huffmancode(std::fstream& input) {
    /* Leemos el numero de bits */
    unsigned int number_of_bits;
    input.read((char*)&number_of_bits, sizeof(unsigned int));

    /* Calculamos el tamaño de la secuencia */
    unsigned int len;
    if (number_of_bits % 8 == 0) {
        len =  number_of_bits/8;
    }
    else {
        len =  (number_of_bits/8) + 1;
    }

    /* Escribimos la secuencia */
    unsigned char * code = new unsigned char[len];
    input.read((char *)code, sizeof(unsigned char)*len);

    return std::make_pair(number_of_bits, code);
}

/* Escribimos el mapa de frecuencias en el binario */
void Huffman::IOS::serialize_freq(std::fstream& output, std::unordered_map<char, int>& freq) {
    /* Escribimos el tamaño del mapa */
    int size = freq.size();
    output.write((char*)&size, sizeof(int));

    /* Escribimos cada par clave-valor */
    for (const auto& pair: freq) {
        output.write((char*)&pair.first, sizeof(char));
        output.write((char*)&pair.second, sizeof(int));
    }
}

/* Obtenemos el mapa de frecuencias a partir del binario */
std::unordered_map<char, int> Huffman::IOS::unserialize_freq(std::fstream& input) {
    /* Obtenemos el tamaño del mapa */
    int size;
    input.read((char*)&size, sizeof(int));
    std::unordered_map<char, int> freq{(size_t)size};

    /* Obtenemos cada par clave-valor */
    char key;
    int value;
    for (int i = 0; i < size; i++) {
        input.read((char*)&key, sizeof(char));
        input.read((char*)&value, sizeof(int));
        freq[key] = value;
    }

    return freq;
}