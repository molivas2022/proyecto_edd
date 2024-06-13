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
     * @brief Inserta una palabra con un maximo de n carateres en el Trie si no ha sido insertada previamente.
     * Se asigna un índice único a la palabra igual al start dado (poscición del primer character en la palabra original).
     * Las palabras son asignadas desde el inicio dado es decir word[start] hasta la cantidad de max_characters elegida.
     * @param word: Palabra a ser añadida al Trie.
     * @param start: Indice del primer caracter de la palabra a insertar.
     * @param end: Indice del ultimo caracter de la palabra a insertar.
     */
    void insert(std::string &word, int start, int end);

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
     * @brief Busca el substring más largo desde el start dado del string dado que coincida con un substring en el Trie.
     * @param str: El string del cual se quiere encontrar el substring más largo en común dentro del Trie.
     * @param start: Desde donde buscaremos el match más grande.
     * @note Esta función esta creada especialmente para el caso de uso en la compresión LZ.
     */
    std::pair<int, char> find_longest_match(std::string &str, int start);
};