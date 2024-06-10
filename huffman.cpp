#include "huffman.h"

#include <iostream>
#include <queue>
#include <stack>

/* -- Funciones y estructuras auxiliares -- */

struct Node {
    char symbol;
    int frequency;
    Node * left;
    Node * right;
};

/* Combina dos nodos como hijos de un nodo padre, */
/* el cual tiene como frecuencia la suma de la frecuencia de sus hijos */
Node * combineNodes(Node *, Node *);

/* Clase comparativa: Criterio de comparación, frecuencias */
struct nodeComparator {
    bool operator()(const Node * node1, const Node * node2) const {
        return node1->frequency > node2->frequency;
    }
};

/* Obtiene las frecuencias de cada caracter en un texto */
std::unordered_map<char, int> readFrequencies(const std::string&);

/* Crea nodos hoja del arbol de Huffman a partir del mapa de frecuencias */
std::priority_queue<Node *, std::vector<Node*>, nodeComparator> createLeaves(const std::unordered_map<char, int>&);

/* Crea el arbol de Huffman a partir de un texto y su mapa de frecuencias */
Node * createHuffmanTree(std::string, std::unordered_map<char, int>);

/* Busca un valor en un arbol binario de Huffman, creando su camino. Recursiva */
bool searchValue(Node *, char, std::string&);

/* Crea diccionarios de codificación y decodificación a partir de un arbol de Huffman */
std::pair<std::unordered_map<char, std::string>, std::unordered_map<std::string, char>> getMaps(Node * huff, std::unordered_map<char, int> map);

/* -- Implementación header -- */

std::string HuffmanCoding::encode(std::string text) {
    
    /* Obtiene la frecuencia de cada caracter del texto */
    auto freq_map = readFrequencies(text);

    /* Crea el arbol de Huffman del texto */                  
    auto huffman_tree = createHuffmanTree(text, freq_map);

    /* Obtiene la codificación y decodificación (en mapas) de los caracteres */
    auto dicts = getMaps(huffman_tree, freq_map);
    auto coding = dicts.first;
    auto decoding = dicts.second;

    /* skibidi biden */
    for (auto it = coding.begin(); it != coding.end(); it++) {

        auto key = it->first;
        std::cout << "'" << key << "' :     " << coding[key] << std::endl;
    }

    return "TO DO.";
}

/* -- Implementación funciones auxiliares -- */

Node * combineNodes(Node * node1, Node * node2) {
    Node * newnode = new Node{'~', node1->frequency + node2->frequency, node1, node2};
    return newnode;
}

std::unordered_map<char, int> readFrequencies(const std::string& str) {
    std::unordered_map<char, int> counter;
    for (int i = 0; i < str.size(); i++) {
        counter[str[i]]++;
    }
    return counter;
}

std::priority_queue<Node *, std::vector<Node*>, nodeComparator> createLeaves(const std::unordered_map<char, int>& map) {
    std::priority_queue<Node *, std::vector<Node*>, nodeComparator> queue;
    for (std::pair<char, int> pair: map) {
        queue.push(new Node{pair.first, pair.second, nullptr, nullptr});
    }
    return queue;
}

Node * createHuffmanTree(std::string str, std::unordered_map<char, int> freq) {
    auto queue = createLeaves(freq);
    while (queue.size() > 1) {
        auto node1 = queue.top(); queue.pop();
        auto node2 = queue.top(); queue.pop();
        queue.push(combineNodes(node1, node2));
    }
    return queue.top(); /* Head */
}

bool searchValue(Node * node, char target, std::string& path) {
    if (!node) {
        return false;
    }
    if (node->symbol == target) {
        return true;
    }

    /* Left */
    path.push_back('0');
    bool cond1 = searchValue(node->left, target, path);
    if (cond1) {return true;}
    path.pop_back();
    
    /* Right */
    path.push_back('1');
    bool cond2 = searchValue(node->right, target, path);
    if (cond2) {return true;}
    path.pop_back();

    return false;
}

std::pair<std::unordered_map<char, std::string>, std::unordered_map<std::string, char>> getMaps(Node * huff, std::unordered_map<char, int> map) {
    std::unordered_map<char, std::string> code;
    std::unordered_map<std::string, char> decode;

    for (auto it = map.begin(); it != map.end(); it++) {
        auto key = it->first;
        std::string path;
        if (!searchValue(huff, key, path)) {
            exit(EXIT_FAILURE); /* Siempre deberia encontrar un camino */
        }
        code.insert({key, path});
        decode.insert({path, key});
    }

    return std::make_pair(code, decode);
}

/* -- Deprecated -- */

void _inOrderTraversal(Node * node, int level) {
    if (node != nullptr) {
            _inOrderTraversal(node->left, level + 1);
            std::cout << level << "\t" << node->symbol << "\t" << node->frequency << std::endl;
            _inOrderTraversal(node->right, level + 1);
        }
}

void inOrderTraversal(Node * head) {
    std::cout << "Level\tSymbol\tFrequency" << std::endl;
    _inOrderTraversal(head, 0);
}