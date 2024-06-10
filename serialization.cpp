#include "huffman.h"
#include "huffman.cpp"

#include <iostream>
#include <fstream>

/* Escribimos el mapa de frecuencias en el binario */
void serialize_freq(std::ofstream& output, std::unordered_map<char, int>& freq) {
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
std::unordered_map<char, int> unserialize_freq(std::ifstream& input) {
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

/* Ejemplo de uso */
int test() {
    auto pre_freq = readFrequencies("ababdaaaacbacab");
    for (auto const& pair: pre_freq) {
        std::cout << pair.first << '\t' << pair.second << std::endl;
    }
    
    std::ofstream write{"test", std::ios::binary};
    serialize_freq(write, pre_freq);
    write.close();

    std::ifstream read{"test", std::ios::binary};
    auto post_freq = unserialize_freq(read);
    read.close();

    std::cout << std::endl;

    for (auto const& pair: post_freq) {
        std::cout << pair.first << '\t' << pair.second << std::endl;
    }

    return 0;
}