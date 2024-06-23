#pragma once

#include <iostream>
#include <fstream>
#include <string>

/* Recorta el tamaño de un archivo de texto a un tamaño deseado (en bytes) */
void cut_file(size_t size, const char *input_filename, const char *output_filename);

/* Compara dos archivos e imprime un mensaje confirmando si contienen exactamente la misma información */
void compare_file(const char* &archivo1, const char* &archivo2);