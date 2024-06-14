#pragma once

#include <string>
#include <unordered_map>
#include <queue>

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

/* Permite codificar y decodificar un texto según la codificación de Huffman */
/* Almacena el arbol de codificación de sólo el último texto codifcado */
namespace Huffman
{
    /* Estructuras auxiliares */

    struct Node {
        char symbol;
        int frequency;
        Node * left;
        Node * right;
    };

    /* Clase comparativa: Devuelve verdadero si node1 es "mayor" que node2 */
    /* Criterios de comparación: Frecuencia -> Simbolo -> Hijo izquierdo -> Hijo derecho -> Son iguales */
    /* Importante (Solución parche): Debe ser una relación de orden total */
    struct nodeComparator {
        bool operator()(const Node * node1, const Node * node2) const {
            if (node1 && !node2) return true;
            if (!node1) return false;
            if (node1->frequency == node2->frequency) {
                if (node1->symbol == node2->symbol) {
                    /* Se comparan los hijos izquierdos */
                    auto left = nodeComparator()(node1->left, node2->left);
                    auto inv_left = nodeComparator()(node2->left, node1->left);
                    if (left != inv_left) return left;

                    /* Se comparan los hijos derechos */
                    return nodeComparator()(node1->right, node2->right);
                }
                return node1->symbol > node2->symbol;
            }
            return node1->frequency > node2->frequency;
        }
    };

    /* Variables de namespace */

    extern Node* LastSavedTree;

    /* Funciones de namespace */

    /* Combina dos nodos como hijos de un nodo padre, el cual tiene como frecuencia la suma de la frecuencia de sus hijos */
    Node * combineNodes(Node *, Node *);

    /* Obtiene las frecuencias de cada caracter en un texto */
    std::unordered_map<char, int> readFrequencies(std::fstream& textfin);

    /* Crea nodos hoja del arbol de Huffman a partir del mapa de frecuencias */
    std::priority_queue<Node *, std::vector<Node*>, nodeComparator> createLeaves(const std::unordered_map<char, int>&);

    /* Crea el arbol de Huffman a partir de un texto y su mapa de frecuencias */
    Node * createHuffmanTree(std::unordered_map<char, int> freq);

    /* Busca un valor en un arbol binario de Huffman, creando su camino. Recursiva */
    bool searchValue(Node *, char, std::string&);

    /* Crea diccionarios de codificación y decodificación a partir de un arbol de Huffman */
    std::pair<std::unordered_map<char, std::string>, std::unordered_map<std::string, char>> getMaps(Node * huff, std::unordered_map<char, int> map);
}

#endif