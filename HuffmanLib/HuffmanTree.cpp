/**
 * huffmanTree.cpp
 * 
 * Implementation file for the HuffmanTree class
 * 
 * Author: Michael White
 * Date: 04/04/2018
 */

#include "huffman.h"
#include <queue>

using WHTMIC023::HuffmanTree;
using WHTMIC023::HuffmanNode;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::unordered_map;

class Compare { // comparator for priority queue
    public:
        bool operator()(const HuffmanNode & a, const HuffmanNode & b) {
            return (a > b);
        }
};

void HuffmanTree::letterFreq(string filepath) {
    frequencies.clear();
    std::ifstream in = std::ifstream(filepath);
    string line;
    while (std::getline(in, line)) {

        for (int i = 0; i < line.length(); i++) {
            char c = line[i];
            if (frequencies.find(c) != frequencies.end()) {
                frequencies[c]++;
            }
            else {
                frequencies[c] = 1;
            }
        }
        if (frequencies.find('\n') != frequencies.end()) {
            frequencies['\n']++;
        }
        else {
            frequencies['\n'] = 1;
        }
    }
    std::cout << "Calculated frequencies!" << std::endl;
}

void HuffmanTree::buildTree() {
    std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, Compare> nodes;
    root = nullptr;

    // push initial nodes onto the queue
    for (auto iter = frequencies.begin(); iter != frequencies.end(); iter++) {
        HuffmanNode n = HuffmanNode(iter-> first, iter -> second);
        nodes.push(n);
    }

    // pop lowest two, combine and repush until only one node left
    while (nodes.size() > 1) {
        HuffmanNode left = nodes.top();
        nodes.pop();
        HuffmanNode right = nodes.top();
        nodes.pop();
        HuffmanNode parent = HuffmanNode(left, right);
        nodes.push(parent);
    }

    // assign the last node to the root
    root = make_shared<HuffmanNode>(std::move(nodes.top()));
    std::cout << "Built Huffman Tree!" << std::endl;
}

HuffmanTree::HuffmanTree(string filepath) { // default constructor
    letterFreq(filepath);
    buildTree();
}

HuffmanTree::HuffmanTree(const HuffmanTree & rhs) { // copy constructor    
    frequencies = rhs.frequencies;
    root = rhs.root;
}

HuffmanTree::HuffmanTree(HuffmanTree && rhs) { // move constructor
    root = rhs.root;
    frequencies = std::move(rhs.frequencies);
    rhs.root = nullptr;
}

HuffmanTree & HuffmanTree::operator=(const HuffmanTree & rhs) { // copy assignment operator
    if (this != &rhs) {
        frequencies = rhs.frequencies;
        root = rhs.root;
    }
    return *this;
}

HuffmanTree & HuffmanTree::operator=(HuffmanTree && rhs) { // move assignment operator
    if (this != &rhs) {
        root = rhs.root;
        frequencies = std::move(rhs.frequencies);
        rhs.root = nullptr;
    }
    return *this;
}

HuffmanTree::~HuffmanTree() { // destructor
    if (root != nullptr) {
        root = nullptr;
        frequencies.clear();
    }
    std::cout << "Destroying tree..." << std::endl;
}