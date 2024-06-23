#include "huffman_serialization.h"
#include "lz77_serialization.h"
#include <chrono>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>

/* Compilación:
 *       g++ test.cpp huffman_tree.cpp huffman_coding.cpp huffman_serialization.cpp lz77_trie.cpp lz77_compression.cpp lz77_serialization.cpp -I headers/ -Wall -Wextra -o test
 */

/* -- Métodos auxiliares -- */

class Clock {
    std::chrono::high_resolution_clock::time_point _start;
    std::chrono::high_resolution_clock::time_point _lap;
public:
    Clock();
    /* Inicia el cronometro */
    void start();
    /* Devuelve el tiempo (en milisegundos) desde el último llamado a lap() */
    /* Si no se ha llamado previamente a lap(), devuelve el tiempo desde el llamado a start() */
    double lap();
    /* Devuelve el tiempo (en milisegundos) desde el llamado a start() */
    double now();
};

std::streampos getFileSize(const std::string& fileName);

/* -- Test --*/
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Uso del programa: ./ejecutable <path a archivo de entrada> <encode/compress>" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    /* Formato de salida:
     * <tipo de compresión>;<tiempo de compresión>[ms];<tiempo de decompresión>[ms];<tamaño descomprimido>[bytes];<tamaño comprimido>[bytes]
     */

    Clock c;
    auto original_size = getFileSize(argv[1]);

    if (strcmp(argv[2], "encode") == 0) {
        c.lap();
        encode_file(argv[1], "encoded");
        auto encoding_time = c.lap();
        auto encoding_size = getFileSize("encoded");

        c.lap();
        decode_file("encoded", "decoded");
        auto decoding_time = c.lap();

        std::cout << "huffman;" << encoding_time << ";" << decoding_time << ";" << original_size << ";" << encoding_size << std::endl;
    }

    else if (strcmp(argv[2], "compress") == 0) {
        c.lap();
        compress_file(argv[1], "compressed", 24, (size_t)8*(size_t)1024*(size_t)1024*(size_t)1024);
        auto compression_time = c.lap();
        auto compression_size = getFileSize("compressed");

        c.lap();
        decompress_file("compressed", "decompressed");
        auto decompression_time = c.lap();

        std::cout << "lz77;" << compression_time  << ";" << decompression_time << ";" << original_size << ";" << compression_size << std::endl;
    }

    return 0;
}

/* -- Implementación métodos auxiliares -- */

Clock::Clock() {
    start();
}

void Clock::start() {
    using namespace std::chrono;
    _start = high_resolution_clock::now(); /* inicializa el cronometro */
    _lap = high_resolution_clock::now();
}

double Clock::lap() {
    using namespace std::chrono;
    high_resolution_clock::time_point _lastlap = _lap; /* llamado anterior a lap() */
    _lap = high_resolution_clock::now(); /* nuevo llamado a lap() */
    return duration_cast<nanoseconds>(_lap - _lastlap).count() * 1e-6; /* diferencia en milisegundos */
}

double Clock::now() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(high_resolution_clock::now() - _start).count() * 1e-6; /* diferencia en milisegundos */
}

std::streampos getFileSize(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary | std::ios::ate); // Open file at the end
    if (file.is_open()) {
        std::streampos size = file.tellg(); // Get position of the end of the file (file size)
        file.close();
        return size;
    } else {
        std::cerr << "Failed to open the file.\n";
        return -1; // Return -1 if the file couldn't be opened
    }
}
