#include <iostream>
#include <vector>
#include <string>

/**
 * Referencias: https://www.geeksforgeeks.org/trie-insert-and-search/
 */

/**
 * Estructura que representa un nodo dentro de un Trie.
 * Cada nodo puede contiene:
 * - Un caracter.
 * - Un índice que indica si el nodo marca el final de una palabra insertada.
 *   - Si el índice es -1, el nodo no representa el final de una palabra.
 *   - Si el índice es un número mayor o igual a 0, el nodo es el final de una palabra y el valor es su índice.
 * - Una lista de nodos hijos 'childs', que pueden ser todos los caracteres posibles (hasta 255 en ASCII).
 */
struct TrieNode
{
    char ch;
    int word_index;
    std::vector<TrieNode *> childs;

    /**
     * Constructor del nodo Trie.
     * Inicializa el nodo con un caracter 'ch' y establece el índice de la palabra en -1.
     */
    TrieNode(char ch)
    {
        this->ch = ch;
        this->word_index = -1;
    }

    /**
     * @brief Busca entre los hijos del nodo actual por un nodo con el caracter 'c'.
     * @param c: Caracter del nodo hijo que se está buscando.
     * @return Puntero al nodo hijo si existe, o un puntero nulo si no.
     */
    TrieNode *get_child(char c)
    {
        if (!childs.empty())
        {
            for (TrieNode *child : childs)
            {
                if (child->ch == c)
                {
                    return child;
                }
            }
        }
        return nullptr; // No se encontró un hijo con el caracter 'c'.
    }
};

/**
 * Clase que representa un árbol Trie para almacenar cadenas de texto.
 * Las cadenas insertadas se les asigna un índice basado en el orden de inserción.
 */
class Trie
{
    TrieNode *root;      //< Nodo raíz del Trie.
    int index_count = 0; //< Contador de índices, aumenta con cada palabra insertada.

public:
    /**
     * Constructor del Trie.
     * Inicializa el Trie con un nodo raíz vacío.
     */
    Trie()
    {
        root = new TrieNode('\0');
    }

    /**
     * Destructor del Trie.
     * Libera la memoria de todos los nodos del Trie.
     */
    ~Trie()
    {
        delete_nodes(root);
    }

    /**
     * @brief Inserta una palabra en el Trie si no ha sido insertada previamente.
     * Se asigna un índice único a la palabra basada en el orden de inserción.
     * @param word: Palabra a ser añadida al Trie.
     */
    void insert(std::string word)
    {
        TrieNode *current_node = root;
        for (char c : word)
        {
            TrieNode *aux = current_node->get_child(c);
            if (aux)
            {
                current_node = aux;
            }
            else
            {
                TrieNode *new_node = new TrieNode(c);
                current_node->childs.push_back(new_node);
                current_node = new_node;
            }
        }
        if (current_node->word_index == -1) // Solo asigna índice si el nodo no tiene uno.
            current_node->word_index = index_count++;
    }

    /**
     * @brief Busca una palabra en el Trie.
     * Si la palabra existe, devuelve su índice, de lo contrario, devuelve -1.
     * @param word: Palabra a buscar en el Trie.
     * @return Índice de la palabra o -1 si no se encuentra.
     */
    int find(std::string word)
    {
        TrieNode *current_node = root;

        for (char c : word)
        {
            if (current_node->get_child(c) == nullptr)
            {
                return -1;
            }
            else
            {
                current_node = current_node->get_child(c);
            }
        }

        return current_node->word_index;
    }

private:
    /**
     * @brief Función recursiva que elimina todos los nodos en un subárbol a partir de un nodo raíz.
     * @param node: Puntero al nodo raíz del subárbol a eliminar.
     */
    void delete_nodes(TrieNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        for (TrieNode *child : node->childs)
        {
            delete_nodes(child);
        }
        delete node;
    }
};

int main()
{
    Trie test_trie = Trie();

    test_trie.insert("hola");
    std::cout << test_trie.find("hola") << std::endl;
    test_trie.insert("ho");
    std::cout << test_trie.find("ho") << std::endl;
    return 0;
}