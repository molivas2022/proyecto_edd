#pragma once

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