#pragma once

#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief Recorta el tamaño de un archivo de texto a un tamaño deseado (en bytes).
 * @param size: tamaño deseado.
 * @param input_filename: nombre del archivo de entrada.
 * @param output_filename: nombre del archivo de salida.
 */
void cut_file(size_t size, const char *input_filename, const char *output_filename);