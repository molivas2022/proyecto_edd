#pragma once
#include <vector>
#include <string>

using namespace std; /* >.< */

/* -- Funciones principales -- */
/* Comprime un archivo input, creando un archivo output */
void compress_file(const char *input_filename, const char *output_filename);
/* Descomprime un archivo input, creando un archivo output */
void decompress_file(const char *input_filename, const char *output_filename);

/* -- Funciones auxiliares -- */
/* Comprime un string, la compresión corresponde a un vector de pares indice-longitud */
vector<pair<int, int>> compress_string(string input);
/* Devuelve un string descomprimido, dado su compresión como un vector de pares de indice-longitud */
string decompress_string(vector<pair<int, int>> input);
pair<string, int> longest_repeated_ocurrence(string search, string look);

/* -- Funciones de depuración -- */
/* Recorta el tamaño de un archivo de texto a un tamaño deseado (en bytes) */
void cut_file(int size, const char *input_filename, const char *output_filename);
/* Imprime los pares indice-longitud de una compresión */
void print_code(vector<pair<int, int>> code);