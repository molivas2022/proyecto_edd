#include <fstream>
#include <iostream>

class HuffmanFileStream {
public:
    void write_encoded_msg(std::string);
    std::string msg_to_string(std::ifstream& file);
};