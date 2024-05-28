#include "huffman.h"

#include <iostream>

int main() {
    HuffmanCoding hc;
    hc.encode("estructura");
    std::cout << std::endl;
    hc.encode("la_luna_llena_ilumina_la_llanura_mientras_las_llamas_la_miran");
}