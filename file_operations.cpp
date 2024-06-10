#include "file_operations.h"

void HuffmanFileHandler::write_encoded_msg(std::string encoded_str)
{
    std::ofstream ofs;
    ofs.open("encoded_msg.txt", std::ofstream::out);
    ofs.write(encoded_str.c_str(),encoded_str.size());
    ofs.close();
}