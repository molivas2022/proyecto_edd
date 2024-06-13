#pragma once
#include <vector>
#include <string>

using namespace std; /* >.< */

/* -- Funciones principales -- */

/**
 * @brief Comprime un archivo input mediante el método de compresión LZ77-trie.
 * @param input_filename: nombre del archivo de entrada.
 * @param output_filename: nombre del archivo de salida.
 * @return Nuevo archivo con la compresión aplicada con el nombre 'output_filename'
 */
void compress_file(const char *input_filename, const char *output_filename);

/**
 *  @brief Descomprime un archivo input, creando un archivo output. La compresión de este archivo tiene que ser
 * del tipo LZ77-trie.
 * @param input_filename: nombre del archivo de entrada.
 * @param output_filename: nombre del archivo de salida.
 * @return Nuevo archivo con la descompresión aplicada con el nombre 'output_filename'
 */
void decompress_file(const char *input_filename, const char *output_filename);

/* -- Funciones auxiliares -- */

/**
 * @brief Comprime un string, la compresión corresponde a un vector de pares indice-longitud.
 * @param input: string a comprimir.
 * @return Vector con pares de compresión LZ77.
 */
vector<pair<int, char>> compress_string(string input);

/**
 * @brief Devuelve un string descomprimido, dado su compresión como un vector de pares de indice-longitud.
 * @param input: Vector con pares de compresión LZ77.
 * @return String descomprimido.
 */
string decompress_string(vector<pair<int, char>> input);

/* -- Funciones de depuración -- */

/* Recorta el tamaño de un archivo de texto a un tamaño deseado (en bytes) */
void cut_file(int size, const char *input_filename, const char *output_filename);

/* Imprime los pares indice-longitud de una compresión */
void print_code(vector<pair<int, char>> code);

// Fuente: Chat GPT ;)
void compararArchivos(const std::string &archivo1, const std::string &archivo2);