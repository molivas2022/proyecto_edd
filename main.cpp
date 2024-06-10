#include "huffman.h"
#include "file_operations.h"
#include <vector>
#include <iostream>

int main() {
    HuffmanCoding hc;
    HuffmanFileStream hfs;
    std::cout << hc.str_encode("estructura") << std::endl;
    hc.str_encode("la_luna_llena_ilumina_la_llanura_mientras_las_llamas_la_miran");
    std::cout << hc.str_encode("la_luna_llena_ilumina_la_llanura_mientras_las_llamas_la_miran") << std::endl;
    hfs.write_encoded_msg(hc.str_encode("la_luna_llena_ilumina_la_llanura_mientras_las_llamas_la_miran"));
}