#include "lz77_trie.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>

/**
 * Referencias: https://www.geeksforgeeks.org/trie-insert-and-search/
 */

/**
 * Constructor del nodo Trie.
 * Inicializa el nodo con un caracter 'ch' y establece el índice de la palabra en -1.
 */
TrieNode::TrieNode(char c)
{
    ch = c;
    word_index = -1;
}

/**
 * Constructor del arbol Trie.
 * Crea la raiz del arbol e inicializa index_count a 0.
 */
Trie::Trie()
{
    root = new TrieNode('\0');
    index_count = 0;
}

Trie::~Trie()
{
    delete_subtree(root);
}

void Trie::delete_subtree(TrieNode *node)
{
    for (auto child : node->childs)
    {
        delete_subtree(child.second);
    }
    delete node;
}

void Trie::insert(std::string &word, int start, int end)
{
    TrieNode *current_node = root;

    // En el final de la palabra original se podria pasar de largo, esta para prevenir.
    std::size_t range_end = std::min((std::size_t)(end), word.length());

    for (std::size_t i = start; i < range_end; i++)
    {
        char ch = word[i];

        // si no se encuentra ningun nodo con este character, se crea uno nuevo
        if (current_node->childs.find(ch) == current_node->childs.end())
        {
            current_node->childs[ch] = new TrieNode(ch);
        }

        // Accedemos al nodo hijo que tiene el character o que creamos creado
        current_node = current_node->childs[ch];

        // Cambiamos los indices en todos los characters de la palabra para que sean el mismo número.
        if (current_node->word_index == -1)
        {
            current_node->word_index = start;
        }
    }
}

bool Trie::find(std::string word)
{
    TrieNode *current_node = root;

    for (std::size_t i = 0; i < word.size(); i++)
    {
        char ch = word[i];

        // Si no existe un nodo con el character, no está la palabra.
        if (current_node->childs.find(ch) == current_node->childs.end())
        {
            return false;
        }
        // Cambiamos a un hijo del nodo actual
        current_node = current_node->childs[ch];
    }
    // Si siempre se encontro un character, entonces la palabra esta insertada en el Trie
    return true;
}

std::pair<int, char> Trie::find_longest_match(std::string &str, int start)
{
    TrieNode *current_node = root;
    int length = 0;
    int index = -1;

    for (std::size_t i = start; i < str.length(); i++)
    {
        char ch = str[i];
        // Si el carácter actual no se encuentra en los hijos del nodo actual, se detiene la búsqueda
        if (current_node->childs.find(ch) == current_node->childs.end())
        {
            break;
        }
        // Si el carácter actual se encuentra en el Trie, actualiza el nodo current.
        current_node = current_node->childs[ch];

        // se actualizan el índice y la longitud de la coincidencia
        if (current_node->word_index != -1)
        {
            index = current_node->word_index;
            length = i - start + 1;
        }
    }

    return std::pair<int, int>(index, length);
}