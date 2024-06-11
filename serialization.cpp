#include "huffman.h"
#include "huffman.cpp"

#include <iostream>
#include <fstream>

void serialize_huffmancode(std::fstream& output, const unsigned int& number_of_bits, unsigned char * code) {
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

std::pair<unsigned int, unsigned char*> unserialize_huffmancode(std::fstream& input) {
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

    return std::make_pair(len, code);
}

/* Escribimos el mapa de frecuencias en el binario */
void serialize_freq(std::fstream& output, std::unordered_map<char, int>& freq) {
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
std::unordered_map<char, int> unserialize_freq(std::fstream& input) {
    /* Obtenemos el tamaño del mapa */
    int size;
    input.read((char*)&size, sizeof(int));
    std::unordered_map<char, int> freq{size};

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