#include <fstream>
#include <iostream>
#include <unordered_map>

#ifndef HUFFMAN_SERIAL_H
#define HUFFMAN_SERIAL_H

/* -- Funciones principales -- */
/**
 * @brief Recibe un archivo de texto como entrada y lo comprime mediante codificación Huffman, el archivo comprimido corresponde al archivo de salida
 * @param input_filename: nombre del archivo de entrada.
 * @param output_filename: nombre del archivo de salida.
 */
void encode_file(const char* input_filename, const char* output_filename);
/**
 * @brief Recibe un archivo comprimido mediante codificación Huffman como entrada y lo descomprime. El archivo de texto descomprimido corresponde al archivo de salida
 * @param input_filename: nombre del archivo de entrada.
 * @param output_filename: nombre del archivo de salida.
 */
void decode_file(const char* input_filename, const char* output_filename);

namespace Huffman {
    namespace IOS {
        /**
         * @brief Permite ingresar en un archivo comprimido el código Huffman de un texto.
         * @param output: stream (con permisos de escritura) del archivo comprimido
         * @param number_of_bits: largo del código Huffman (en bytes/en cáracteres)
         * @param code: código Huffman expresado como un array de cáracteres.
         */
        void serialize_huffmancode(std::fstream& output, const unsigned int& number_of_bits, unsigned char * code);
        /**
         * @brief Permite obtener el código Huffman de un archivo comprimido.
         * @param input: stream (con permisos de lectura) del archivo comprmido
         * @return Par de valores donde: el segundo es el código Huffman expresado como array de cáracteres; el primero es el número de cáracteres
         */
        std::pair<unsigned int, unsigned char*> unserialize_huffmancode(std::fstream& input);
        /**
         * @brief Permite ingresar en un archivo comprimido la tabla de frecuencia con qué aparecen cáracteres en un texto.
         * @param output: stream (con permisos de escritura) del archivo comprimido
         * @param freq: tabla de frecuencias expresado como mapa donde: la clave es un cáracter dado y el valor es la frecuencia de dicho cáracter.
         */
        void serialize_freq(std::fstream& output, std::unordered_map<char, int>& freq);
        /**
         * @brief Permite obtener la tabla de frecuencias de un archivo comprimido.
         * @param input: stream (con permisos de lectura) del archivo comprmido
         * @return tabla de frecuencias expresado como mapa donde: la clave es un cáracter dado y el valor es la frecuencia de dicho cáracter.
         */
        std::unordered_map<char, int> unserialize_freq(std::fstream& input);
    }
}

#endif