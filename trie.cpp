#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

/**
 * Referencias: https://www.geeksforgeeks.org/trie-insert-and-search/
 */

struct TrieNode
{
    char ch;
    int word_index;
    // Pensandolo bien quizas es mejor utilizar un unordered map en esto, por la velocidad
    std::unordered_map<char, TrieNode *> childs;

    TrieNode(char ch)
    {
        this->ch = ch;
        this->word_index = -1;
    }
};

class Trie
{
    TrieNode *root;      //< Nodo raíz del Trie.
    int index_count = 0; //< Contador de índices, aumenta con cada palabra insertada.

public:
    Trie()
    {
        root = new TrieNode('\0');
    }

    ~Trie()
    {
        // AQUI HABRIA QUE PONER UN DESTRUCTOOOOOR (TOMANDO EN CUENTA EL UNORDEREDMAP)
    }

    void insert(std::string word)
    {
        TrieNode *current_node = root;

        for (std::size_t i = 0; i < word.size(); i++)
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
                current_node->word_index = index_count;
            }
        }
        index_count++;
    }

    bool find(std::string word)
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

    std::pair<int, int> find_longest_match(std::string str)
    {
        TrieNode *current_node = root;
        int length = 0;
        int index = -1;

        for (std::size_t i = 0; i < str.size(); i++)
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
                length = i + 1;
            }
        }

        return std::pair<int, int>(index, length);
    }
};