#pragma once

/* límite de memoria máxima (en bytes) por defecto del trie */
size_t DEFAULT_MEMORY_LIMI = (size_t)2*(size_t)1024*(size_t)1024*(size_t)1024;

/* -- Funciones principales -- */

/**
 * @brief Comprime un archivo input mediante el método de compresión LZ77-trie.
 * @param input_filename: nombre del archivo de entrada.
 * @param output_filename: nombre del archivo de salida.
 * @param MAX_BUFFER: distancia de visión de las ventanas. (si se aumenta se traduce en reutilización de strings mas largos) por defecto es 24.
 * @param MEMORY_LIMIT: memoria máxima (en bytes) que puede utilizar el trie. si el limite se sobrepasa el trie se limpia. por defecto es 2gb.
 * si es igual a -1 (por defecto), no hay limite de memoria.
 * @return Nuevo archivo con la compresión aplicada con el nombre 'output_filename'
 */
void compress_file(const char *input_filename, const char *output_filename, int MAX_BUFFER = 24, size_t MEMORY_LIMI = DEFAULT_MEMORY_LIMI);

/**
 *  @brief Descomprime un archivo input, creando un archivo output. La compresión de este archivo tiene que ser
 * del tipo LZ77-trie.
 * @param input_filename: nombre del archivo de entrada.
 * @param output_filename: nombre del archivo de salida.
 * @return Nuevo archivo con la descompresión aplicada con el nombre 'output_filename'
 */
void decompress_file(const char *input_filename, const char *output_filename);