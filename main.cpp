#include "huffman_serialization.h"
#include "lz77_serialization.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>

/* Durante ejecución, recibe como único parámetro un archivo de texto el cual codificar mediante árbol de Huffman
*
*   Compilación: 
*       g++ main.cpp huffman_tree.cpp huffman_coding.cpp huffman_serialization.cpp lz77_trie.cpp lz77_compression.cpp lz77_serialization.cpp -I headers/ -Wall -Wextra -o main
*/
int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Uso del programa: ./ejecutable <operacion> <path a archivo de entrada> <nombre de archivo de salida>" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[1],"encode") == 0) {
        encode_file(argv[2], argv[3]);
    }
    else if (strcmp(argv[1],"decode") == 0) {
        decode_file(argv[2], argv[3]);
    }
    else if (strcmp(argv[1],"compress") == 0) {
        compress_file(argv[2], argv[3]);
    }
    else if (strcmp(argv[1],"decompress") == 0) {
        decompress_file(argv[2], argv[3]);
    }
    return 0;
}

