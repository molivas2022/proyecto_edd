#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "lz77_compression.h"
#include "lz77_trie.h"

using namespace std; /* >.< */

/* Fuente: https://en.wikipedia.org/wiki/LZ77_and_LZ78#LZ77 */
vector<pair<int, char>> compress_string(string input)
{
    /* Variables */
    vector<pair<int, char>> output;
    Trie trie;
    int MAX_BUFFER = 32;
    int search_buffer_left = 0;

    pair<int, char> aux;

    /* Loop */
    int input_index = 0;
    while (input_index < input.length())
    {
        // Si la direfencia entre el límite inferior y el superior sobrepasa el máximo,
        // se recalcula el límite inferior
        if (input_index - search_buffer_left > MAX_BUFFER)
        {
            search_buffer_left = input_index - MAX_BUFFER;
        }

        // Buscamos el "match", más largo que se encuentre añadido en el trie.
        aux = trie.find_longest_match(input, input_index);
        int index = aux.first;
        int length = aux.second;

        // Si el match más largo es 0, entonces es una palabar nunca vista, guardamos (char,0)
        if (length == 0)
        {
            output.emplace_back((int)input[input_index], (char)0);

            // Además guardamos en el trie todos los suffix que se pueden generar de la palabra que está en el
            // search buffer
            for (int i = search_buffer_left; i < input_index; i++)
            {
                trie.insert(input, i, input_index);
            }
            // avanzamos en el string al siguiente character
            input_index++;
        }
        else
        {
            // Si el match es mayor que 0, añadimos el par (index, length)
            output.emplace_back(index, (char)length);

            // Además guardamos en el trie todos los suffix que se pueden generar de la palabra que está en el
            // search buffer
            for (int i = search_buffer_left; i < input_index; i++)
            {
                trie.insert(input, i, input_index);
            }

            // avanzamos en el string la la cantidad de characters que hicieron match.
            input_index += length;
        }

        /* debugging */
        cout << 100.0 * ((float)input_index) / ((float)input.length()) << " %" << endl;
    }

    return output;
}

string decompress_string(vector<pair<int, char>> input)
{
    string output;

    // OJO: los pares estan guardados como (index, lenght)

    int size = input.size();
    for (int i = 0; i < size; i++)
    {
        // recuperamos el primer par y lo guardamos en code.
        auto code = input[i];

        if (code.second == 0)
        {
            // Si el lenght es 0, entonces añadimos el indice como char.
            output.append(string{(char)code.first});
        }
        else
        {
            // Si el lenght mayor a 0, entonces añadimos el subtring que va desde index hasta index + length
            if (output.length() >= code.first + (int)code.second)
            {
                output.append(output.substr(code.first, (int)code.second));
            }
            else
            {
                // Si por alguna razón la compresión esta mal hecha, rompemos el programa y
                // mostramos el par en donde hay un error
                cout << "hubo un error con: (" << code.first << ", " << (int)code.second << ")" << endl;
                break;
            }
        }
    }
    return output;
}

void print_code(vector<pair<int, char>> code)
{
    for (int i = 0; i < code.size(); i++)
    {
        cout << "index: " << i << ", " << "par: ";
        cout << '(';
        if (code[i].second == 0)
        {
            cout << (char)code[i].first;
        }
        else
        {
            cout << code[i].first;
        }
        cout << ", ";
        cout << (int)code[i].second;
        cout << ")  ";
        cout << endl;
    }
}