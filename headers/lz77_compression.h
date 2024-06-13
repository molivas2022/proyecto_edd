#pragma once
#include <vector>
#include <string>

using namespace std; /* >.< */

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

/* Imprime los pares indice-longitud de una compresión */
void print_code(vector<pair<int, char>> code);