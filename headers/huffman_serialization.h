#include <fstream>
#include <iostream>
#include <unordered_map>

#ifndef HUFFMAN_SERIAL_H
#define HUFFMAN_SERIAL_H

/* que haras al respecto, matias */

namespace Huffman {
    namespace IOS {
        void serialize_huffmancode(std::fstream& output, const unsigned int& number_of_bits, unsigned char * code);
        std::pair<unsigned int, unsigned char*> unserialize_huffmancode(std::fstream& input);
        void serialize_freq(std::fstream& output, std::unordered_map<char, int>& freq);
        std::unordered_map<char, int> unserialize_freq(std::fstream& input);
    }
}

#endif