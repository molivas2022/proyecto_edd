#include "huffman.h"

#include <iostream>
#include <queue>
#include <stack>
#include <fstream>

const bool _HUFFMAN_DEBUG = 0;

/* -- Funciones y estructuras auxiliares -- */

struct Node {
    char symbol;
    int frequency;
    Node * left;
    Node * right;
};

struct BitUdec {
    unsigned char val : 1;
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
std::unordered_map<char, int> readFrequencies(std::fstream& textfin);

/* Crea nodos hoja del arbol de Huffman a partir del mapa de frecuencias */
std::priority_queue<Node *, std::vector<Node*>, nodeComparator> createLeaves(const std::unordered_map<char, int>&);

/* Crea el arbol de Huffman a partir de un texto y su mapa de frecuencias */
Node * createHuffmanTree(std::unordered_map<char, int> freq);

/* Busca un valor en un arbol binario de Huffman, creando su camino. Recursiva */
bool searchValue(Node *, char, std::string&);

/* Crea diccionarios de codificación y decodificación a partir de un arbol de Huffman */
std::pair<std::unordered_map<char, std::string>, std::unordered_map<std::string, char>> getMaps(Node * huff, std::unordered_map<char, int> map);

/* debugging :33 :3 */
void printbits(unsigned char v);

/* -- Implementación header -- */

std::string HuffmanCoding::str_encode(std::fstream& ifs) 
{
    auto freq_map = readFrequencies(ifs);           
    auto huffman_tree = createHuffmanTree(freq_map);
    std::string encoded_msg;

    /* Obtiene mapas de codificación y decodificación del texto leído */
    auto dicts = getMaps(huffman_tree, freq_map);
    auto coding = dicts.first;
    auto decoding = dicts.second;

    /* Vuelve al inicio del archivo y define un string con el mensaje codificado */
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    char ch;
    while (ifs >> std::noskipws >> ch) {
        encoded_msg += coding[ch];
    }

    /* DEBUGGING PRINT */
    if (_HUFFMAN_DEBUG) {
        for (auto it = coding.begin(); it != coding.end(); it++) {
            auto key = it->first;
            std::cout << "'" << key << "' :     " << coding[key] << std::endl;
        }
        std::cout << encoded_msg << std::endl;
    }

    return encoded_msg;
}

unsigned char* HuffmanCoding::bit_encode(std::fstream& ifs) 
{
    auto freq_map = readFrequencies(ifs);           
    auto huffman_tree = createHuffmanTree(freq_map);

    /* Obtiene mapas de codificación y decodificación del texto leído */
    auto dicts = getMaps(huffman_tree, freq_map);
    auto coding = dicts.first;
    auto decoding = dicts.second;

    size_t encoded_msg_len = 0;
    unsigned char *encoded_msg;

    /* Computar tamaño del mensaje codificado mediante la tabla de frecuencias, luego pedir memoria heap para arreglo de este tamaño. */
    for (auto it = coding.begin(); it != coding.end(); it++) {
        char key = it->first;
        encoded_msg_len += ((freq_map.find(key))->second)*((coding[key]).length());
    }

    /* Vuelve al inicio del archivo y define un string con el mensaje codificado */
    ifs.clear();
    ifs.seekg(0, std::ios::beg);

    encoded_msg = new unsigned char[(encoded_msg_len/8)+1];
    encoded_msg[0] = (unsigned char)0; // inicializa a 0 para eliminar "basura"
    int EncMsg_idx = 0;
    char current_ch; // char del texto original que se esta leyendo
    int bitflip_pos = 7; // posicion de Izquierda a Derecha (mayor a menor) donde se voltea un bit

    /* me voy a matar ctm (Loop para insertar secuencias de bits en cada byte del arreglo encoded_msg) */
    while (ifs >> std::noskipws >> current_ch) {
        std::string encoded_char = (coding[current_ch]);

        for (int i=0; i < encoded_char.length(); i++) {
            /* cuando un byte del arreglo se llena, incrementar el indice de encoded_msg para asi pasar al siguiente byte */
            if (bitflip_pos < 0) {
                EncMsg_idx++;
                encoded_msg[EncMsg_idx] = (unsigned char)0;
                bitflip_pos = 7;
            }
            /* hacer flip del bit en bitflip_pos (pensando los indices de un byte como decreciendo hacia la derecha) si es que el char codificado posee un 1 en la i-esima posicion*/
            if (encoded_char[i] == '1') {
                encoded_msg[EncMsg_idx] |= ((unsigned char)1 << bitflip_pos);
            }
            bitflip_pos--;
        }
    }

    /* Debugging print */
    if (_HUFFMAN_DEBUG) {
        int char_arr_size = (encoded_msg_len/8)+1;
        std::cout << "char array size: " << char_arr_size << std::endl;
        for (int i=0; i < (encoded_msg_len/8)+1; i++) {
            printbits(encoded_msg[i]);
        }
    }

    return encoded_msg;
}

/* -- Implementación funciones auxiliares -- */

Node * combineNodes(Node * node1, Node * node2) {
    Node * newnode = new Node{'~', node1->frequency + node2->frequency, node1, node2};
    return newnode;
}

/*
* Parámetros:
* - textfin: fstream desde el cual se lee el archivo
*
* Retorna:
* - unordered_map, cuyas claves son los carácteres del archivo, y cuyos valores son la frecuencia asociada al carácter dentro del texto.
*/
std::unordered_map<char, int> readFrequencies(std::fstream& textfin) {
    std::unordered_map<char, int> counter;
    char ch;
    while (textfin >> std::noskipws >> ch) {
        counter[ch]++;
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

Node * createHuffmanTree(std::unordered_map<char, int> freq) {
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

/* debug */
void printbits(unsigned char v) {
    for(int i = 7; i >= 0; i--) putchar('0' + ((v >> i) & 1));
}