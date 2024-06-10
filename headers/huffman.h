#pragma once

#include <string>
#include <unordered_map>

/* Permite codificar y decodificar un texto según la codificación de Huffman */
/* Almacena el arbol de codificación de sólo el último texto codifcado */
class HuffmanCoding {
    std::unordered_map<char, std::string> encoding; /* llave = ascii char, valor = codigo huffman  */
    std::unordered_map<std::string, char> decoding; /* llave = codigo huffman, valor = ascii char */
public:
    std::string str_encode(std::fstream& text);
    unsigned char* bit_encode(std::string);
    std::string decode(std::string);
};