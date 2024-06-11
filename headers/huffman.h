#pragma once

#include <string>
#include <unordered_map>

struct Node {
    char symbol;
    int frequency;
    Node * left;
    Node * right;
};

/* Permite codificar y decodificar un texto según la codificación de Huffman */
/* Almacena el arbol de codificación de sólo el último texto codifcado */
class HuffmanCoding {
    std::unordered_map<char, std::string> encoding; /* llave = ascii char, valor = codigo huffman  */
    std::unordered_map<std::string, char> decoding; /* llave = codigo huffman, valor = ascii char */
public:
    std::string str_encode(std::fstream&);
    std::pair<unsigned int, unsigned char*> bit_encode(std::fstream&);
    std::string bit_decode(unsigned char*, size_t, Node*);
};