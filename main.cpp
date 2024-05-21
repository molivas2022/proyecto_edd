#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <iterator>

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

class HuffmanTree {
    Node * head;
public:
    HuffmanTree(const std::string& str) {
        auto map = readFrequencies(str);
        auto queue = createLeaves(map);
        while (queue.size() > 1) {
            auto node1 = queue.top(); queue.pop();
            auto node2 = queue.top(); queue.pop();
            queue.push(combineNodes(node1, node2));
        }
        head = queue.top();
    }

    void inOrderTraversal() const {
        std::cout << "Level\tSymbol\tFrequency" << std::endl;
        inOrderTraversal(head, 0);
    }

    /* Fuente: ChatGPT señores */
    void inOrderTraversal(Node* node, int level) const {
        if (node != nullptr) {
            inOrderTraversal(node->left, level + 1);
            std::cout << level << "\t" << node->symbol << "\t" << node->frequency << std::endl;
            inOrderTraversal(node->right, level + 1);
        }
    }
};

int main() {
    /* Example*/
    std::string str{"estructura"};

    HuffmanTree * ht = new HuffmanTree{str};
    ht->inOrderTraversal();

    return 0;
}
