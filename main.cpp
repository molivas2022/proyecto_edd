#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <iterator>
#include <stack>

struct Node {
    char symbol;
    int frequency;
    Node * left;
    Node * right;
};

Node * combineNodes(Node * node1, Node * node2) {
    Node * newnode = new Node{'~', node1->frequency + node2->frequency, node1, node2};
    return newnode;
}

struct nodeComparator {
    bool operator()(const Node * node1, const Node * node2) const {
        return node1->frequency > node2->frequency;
    }
};

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

Node * createHuffmanTree(std::string str) {
    auto map = readFrequencies(str);
    auto queue = createLeaves(map);
    while (queue.size() > 1) {
        auto node1 = queue.top(); queue.pop();
        auto node2 = queue.top(); queue.pop();
        queue.push(combineNodes(node1, node2));
    }
    return queue.top(); /* Head */
}

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

auto getMaps(Node * huff, std::unordered_map<char, int> map) {
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

int main() {
    /* Example */
    std::string str{"estructura"};

    auto freq = readFrequencies(str);
    Node * hf = createHuffmanTree(str);

    auto maps = getMaps(hf, freq);
    auto code = maps.first;
    auto decode = maps.second;

    std::cout << code['e'] << std::endl;
    std::cout << code['s'] << std::endl;
    std::cout << code['t'] << std::endl;
    std::cout << code['r'] << std::endl;
    std::cout << code['u'] << std::endl;
    std::cout << code['c'] << std::endl;
    std::cout << code['a'] << std::endl;

    std::cout << decode[std::string("1111")] << std::endl;
    std::cout << decode[std::string("001")] << std::endl;
    std::cout << decode[std::string("01")] << std::endl;
    std::cout << decode[std::string("110")] << std::endl;
    std::cout << decode[std::string("10")] << std::endl;
    std::cout << decode[std::string("000")] << std::endl;
    std::cout << decode[std::string("1110")] << std::endl;

    return 0;
}