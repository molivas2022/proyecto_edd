#pragma once

#include <string>
#include <unordered_map>

/**
 * Estructura auxiliar de Trie. Representa un nodo con un character.
 */
struct TrieNode
{
    char ch;
    int word_index;
    std::unordered_map<char, TrieNode *> childs;

    TrieNode(char c);
};

/**
 * Clase que representa un árbol Trie para almacenar cadenas de texto. Esta implementación esta
 * modificada para ser utilizado como una estructura auxiliar a la compresión LZ.
 * Las cadenas insertadas se les asigna un índice dependiendo del orden de entrada.
 */
class Trie
{
    TrieNode *root;  // Raiz del árbol
    int index_count; // Índice que lleva en la cuanta, este empieza en 0 e incrementa en cada inserción en 1

    /**
     * @brief Elimina todo el sub-arbol que tiene como raiz a node recursivamente.
     * @param node: nodo desde el cual se eliminara el sub-arbol
     */
    void delete_subtree(TrieNode *node);

public:
    /**
     * Constructor del Trie.
     * Inicializa el Trie con un nodo raíz vacío.
     */
    Trie();

    /**
     * Destructor del Trie.
     * Libera la memoria de todos los nodos del Trie.
     */
    ~Trie();

    /**
     * @brief Inserta una palabra en el Trie si no ha sido insertada previamente.
     * Se asigna un índice único a la palabra basada en el orden de inserción.
     * @param word: Palabra a ser añadida al Trie.
     */
    void insert(std::string word);

    /**
     * @brief Busca una palabra en el Trie.
     * Si la palabra existe, devuelve true, si ocurre lo contrario false.
     * @param word: Palabra a buscar en el Trie.
     * @return True si la palabra existe o false si no se encuentra.
     * @note Notemos que en el caso de esta implementación, lo importante no es que la palabra sea exactamente la
     * que se inserto, puede ser un subtring de una palabra ingresada.
     */
    bool find(std::string word);

    /**
     * @brief Busca el substring más largo desde el inicio del string dado que coincida con un substring en el Trie.
     * @param str: El string del cual se quiere encontrar el substring más largo en común dentro del Trie.
     * @note Esta función esta creada especialmente para el caso de uso en la compresión LZ.
     */
    std::pair<int, int> find_longest_match(std::string str);
};