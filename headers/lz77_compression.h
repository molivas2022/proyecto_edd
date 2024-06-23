#pragma once
#include <vector>
#include <string>

using namespace std; /* >.< */

/**
 * @brief Comprime un string, la compresión corresponde a un vector de pares indice-longitud.
 * @param input: string a comprimir.
 * @param MAX_BUFFER: distancia de visión de las ventanas (si se aumenta se traduce en reutilización de strings mas largos), por defecto es 16.
 * @param MEMORY_LIMIT: memoria máxima(kB) que puede utilizar el trie. si el limite se sobrepasa el trie se limpia.
 * si es igual a -1 (por defecto), no hay limite de memoria.
 * @return Vector con pares de compresión LZ77.
 */
vector<pair<int, char>> compress_string(string input, int MAX_BUFFER, size_t MEMORY_LIMIT);

/**
 * @brief Devuelve un string descomprimido, dado su compresión como un vector de pares de indice-longitud.
 * @param input: Vector con pares de compresión LZ77.
 * @return String descomprimido.
 */
string decompress_string(vector<pair<int, char>> input);

/* -- Funciones de depuración -- */

/* Imprime los pares indice-longitud de una compresión */
void print_code(vector<pair<int, char>> code);