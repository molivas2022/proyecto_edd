#include "huffman_tree.h"
#include <unordered_map>
#include <string>

#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H

namespace Huffman 
{
    /* Variables de namespace */

    extern size_t LastSavedSize;

    /* Funciones de namespace */

    /* Antigua función de encoding, inserta el mensaje codificado a un string y lo retorna. */
    std::string str_encode(std::fstream&);

    /* Inserta cada carácter codificado como una secuencia de bits, y cada secuencia de bits es insertada a los bytes de un arreglo de unsigned char. */
    std::pair<unsigned int, unsigned char*> bit_encode(std::fstream&);

    /* Decodifica un mensaje que ha sido codificado con bit_encode() */
    std::string bit_decode(unsigned char*, size_t, Node*);
}

#endif