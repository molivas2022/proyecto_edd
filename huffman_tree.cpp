#include "huffman_tree.h"

#include <iostream>
#include <queue>
#include <stack>
#include <fstream>

using namespace Huffman;

Node* Huffman::LastSavedTree = nullptr;

Node * Huffman::combineNodes(Node * node1, Node * node2) {
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
std::unordered_map<char, int> Huffman::readFrequencies(std::fstream& textfin) {
    std::unordered_map<char, int> counter;
    char ch;
    while (textfin >> std::noskipws >> ch) {
        counter[ch]++;
    }
    return counter;
}

std::priority_queue<Node *, std::vector<Node*>, nodeComparator> Huffman::createLeaves(const std::unordered_map<char, int>& map) {
    std::priority_queue<Node *, std::vector<Node*>, nodeComparator> queue;
    for (std::pair<char, int> pair: map) {
        queue.push(new Node{pair.first, pair.second, nullptr, nullptr});
    }
    return queue;
}

Node * Huffman::createHuffmanTree(std::unordered_map<char, int> freq) {
    auto queue = createLeaves(freq);
    while (queue.size() > 1) {
        auto node1 = queue.top(); queue.pop();
        auto node2 = queue.top(); queue.pop();
        queue.push(combineNodes(node1, node2));
    }
    LastSavedTree = queue.top();
    return queue.top(); /* Head */
}

bool Huffman::searchValue(Node * node, char target, std::string& path) {
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

std::pair<std::unordered_map<char, std::string>, std::unordered_map<std::string, char>> Huffman::getMaps(Node * huff, std::unordered_map<char, int> map) {
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