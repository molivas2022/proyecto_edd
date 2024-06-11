#include "huffman.h"
#include "trie.h"
#include "lz77.h"

#include <iostream>

int main()
{
    // FIXME: Por alguna razón no funciona cuando se ponen muchos bytes, nose si es tema de
    // la compresión o si es tema de la descompresión.

    // 299159 es el valor exacto en donde falla.
    cut_file(299159, "sample.txt", "sample_cut.txt"); /* 1048576 bytes = 1 mB */
    compress_file("sample_cut.txt", "sample_compressed.txt");
    decompress_file("sample_compressed.txt", "sample_decompressed.txt");
    /* Notar que sample_cut.txt y sample_decompressed.txt son identicos */
    compararArchivos("sample_cut.txt", "sample_decompressed.txt");

    return 0;
}