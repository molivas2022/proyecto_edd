#include "huffman_tree.h"

#include <iostream>
#include <queue>
#include <stack>
#include <fstream>

using namespace Huffman;

/* Caracter por defecto asignado a nodos NO hojas en el arbol de huffman */
const char DEFAULT_CHARACTER = '~'; /* No implica que sea un caracter ilegal */

Node* Huffman::LastSavedTree = nullptr;

Node * Huffman::combineNodes(Node * node1, Node * node2) {
    Node * newnode = new Node{DEFAULT_CHARACTER, node1->frequency + node2->frequency, node1, node2}; /* Crea el nodo padre */
    return newnode;
}

/*
* Parámetros:
* - textfin: fstream desde el cual se lee el archivo
*
* Retorna:
* - unordered_map, cuyas claves son los carácteres del archivo, y cuyos valores son la frecuencia asociada al carácter dentro del texto.
*/
std::unordered_map<char, int> Huffman::readFrequencies(std::fstream& textfin) {
    std::unordered_map<char, int> counter;
    char ch;
    while (textfin >> std::noskipws >> ch) { /* Leemos cada caracter */
        counter[ch]++; /* Y sumamos en su frecuencia */
    }
    return counter;
}

std::priority_queue<Node *, std::vector<Node*>, nodeComparator> Huffman::createLeaves(const std::unordered_map<char, int>& freq) {
    std::priority_queue<Node *, std::vector<Node*>, nodeComparator> queue;
    for (std::pair<char, int> pair: freq) {
        queue.push(new Node{pair.first, pair.second, nullptr, nullptr});
    }
    return queue;
}

Node * Huffman::createHuffmanTree(std::unordered_map<char, int> freq) {
    auto queue = createLeaves(freq); /* Obtenemos todos los nodos hoja */
    while (queue.size() > 1) {
        auto node1 = queue.top(); queue.pop();
        auto node2 = queue.top(); queue.pop();
        queue.push(combineNodes(node1, node2)); /* Combinamos los dos nodos de mayor prioridad */
    }
    LastSavedTree = queue.top(); /* Ultimo arbol */
    return queue.top(); /* Head */
}

bool Huffman::searchValue(Node * node, char target, std::string& path) {
    if (!node) {
        return false; /* Llegamos al final sin encontrar nada en este camino */
    }
    if (node->symbol == target) {
        /* Debemos asegurarnos que es un nodo hoja */
        if (!(node->left) && !(node->right)) return true;
    }

    /* Probamos con avanzar por el subárbol izquierdo */
    path.push_back('0');
    bool cond1 = searchValue(node->left, target, path);
    if (cond1) {return true; /* En caso de ser el camino correcto */}
    path.pop_back(); /* En caso de que no */
    
    /* Probamos con avanzar por el subárbol derecho */
    path.push_back('1');
    bool cond2 = searchValue(node->right, target, path);
    if (cond2) {return true; /* En caso de ser el camino correcto */}
    path.pop_back(); /* En caso de que no */

    return false;
}

std::pair<std::unordered_map<char, std::string>, std::unordered_map<std::string, char>> Huffman::getMaps(Node * huff, std::unordered_map<char, int> map) {
    std::unordered_map<char, std::string> code; /* mapa de codificación */
    std::unordered_map<std::string, char> decode; /* mapa de decodificación */

    for (auto it = map.begin(); it != map.end(); it++) { /* leemos todos los caracteres distintos */
        auto key = it->first;
        std::string path;
        if (!searchValue(huff, key, path)) { /* y buscamos su camino en el árbol de Huffman -> codificación Huffman */
            exit(EXIT_FAILURE); /* Siempre deberia encontrar un camino */
        }
        code.insert({key, path});
        decode.insert({path, key});
    }

    return std::make_pair(code, decode);
}