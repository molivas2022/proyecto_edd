#include "huffman.h"
#include "file_operations.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

/* Durante ejecución, recibe como único parámetro un archivo de texto el cual codificar mediante árbol de Huffman
*/
int main(int argc, char** argv) {
    HuffmanCoding hc;
    HuffmanFileHandler hfs;
    if (argc == 2) {
        std::fstream ifs(argv[1], std::fstream::in);
        std::string encoded_str = hc.str_encode(ifs);
        hfs.write_encoded_msg(encoded_str);
    }

    return 0;
}