#include "trie.h"
#include "lz77.h"

#include <iostream>

int main()
{

    cut_file(1048576, "sample.txt", "sample_cut.txt"); /* 1048576 bytes = 1 mB */
    compress_file("sample_cut.txt", "sample_compressed.bin");
    decompress_file("sample_compressed.bin", "sample_decompressed.txt");

    compararArchivos("sample_cut.txt", "sample_decompressed.txt");

    return 0;
}