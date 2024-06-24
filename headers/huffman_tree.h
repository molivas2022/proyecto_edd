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
    /* Estructura auxiliar: Corresponde a un nodo en el árbol de Huffman */
    struct Node {
        char symbol; /* Para nodos hojas: Cáracter representado por el nodo */
        int frequency; /* Para nodos hojas: Frecuencia del cáracter. Para nodos internos: Frecuencia de todo el subarbol */
        Node * left; /* Puntero a hijo izquierdo */
        Node * right; /* Puntero a hijo derecho */
    };

    /* Clase comparativa: Devuelve verdadero si node1 es "mayor" que node2 */
    /* Criterios de comparación: Frecuencia -> Simbolo -> Hijo izquierdo -> Hijo derecho -> Son iguales */
    /* Importante: Debe ser una relación de orden total */
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

    extern Node* LastSavedTree; /* Último arbol de Huffman guardado */

    /* Funciones de namespace */

    /**
     * @brief Combina dos nodos como hijos de un nodo padre, el cual tiene como frecuencia la suma de la frecuencia de sus hijos
     * @param node1: Nodo hijo a combinar, notar que puede ser la raiz de un árbol
     * @param node2: Nodo hijo a combinar, notar que puede ser la raiz de un árbol
     * @return Nodo resultado de la combinación
     */
    Node * combineNodes(Node * node1, Node * node2);

    /**
     * @brief Obtiene las frecuencias de cada caracter en un texto
     * @param textfin: stream (con permisos de lectura) del texto
     * @return tabla de frecuencias expresado como mapa donde: la clave es un cáracter dado y el valor es la frecuencia de dicho cáracter
     */
    std::unordered_map<char, int> readFrequencies(std::fstream& textfin);

    /** 
     * @brief Crea nodos hoja del arbol de Huffman a partir del mapa de frecuencias
     * @param freq: tabla de frecuencias expresado como mapa donde: la clave es un cáracter dado y el valor es la frecuencia de dicho cáracter
     * @return Cola de prioridad con todos los nodos hojas del árbol de Huffman
     */
    std::priority_queue<Node *, std::vector<Node*>, nodeComparator> createLeaves(const std::unordered_map<char, int>& freq);

    /**
     * @brief Crea el árbol de Huffman a partir de un texto y su mapa de frecuencias
     * @param freq: tabla de frecuencias expresado como mapa donde: la clave es un cáracter dado y el valor es la frecuencia de dicho cáracter
     * @return Raiz del árbol de Huffman
     */
    Node * createHuffmanTree(std::unordered_map<char, int> freq);

    /**
     * @brief Busca un valor en un arbol binario de Huffman, creando su camino. Recursiva
     * @param node: Raíz del árbol de Huffman. En llamadas recursivas corresponde a raíz de cada subarbol.
     * @param target: Cáracter que se busca.
     * @param path: Camino de 0s y 1s, expresado como string, para llegar al valor deseado desde la raíz. Corresponde al código de Huffman.
     * @return Verdadero si se encontró dicho camino. Falso de caso contrario.
     */
    bool searchValue(Node * node, char target, std::string& path);

    /**
     * @brief Crea diccionarios de codificación y decodificación a partir de un arbol de Huffman
     * @param huff: Raiz del arbol de Huffman
     * @param freq: tabla de frecuencias expresado como mapa donde: la clave es un cáracter dado y el valor es la frecuencia de dicho cáracter
     * @return Par de valores donde:
     *          - el primer valor es un mapa de clave un cáracter del texto, y de valor su codificación Huffman (como string)
     *          - el segundo valor es el mismo mapa pero invertido: de clave la codificación Huffman (como string) y valor el cáracter correspondiente.
     *          - son respectivamente los mapas para codificar y decodificar.
     */
    std::pair<std::unordered_map<char, std::string>, std::unordered_map<std::string, char>> getMaps(Node * huff, std::unordered_map<char, int> map);
}

#endif