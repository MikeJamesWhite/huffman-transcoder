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
            return (a < b);
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
    root = make_shared<HuffmanNode>(nodes.top());
    std::cout << "Built the tree!" << std::endl;
}

HuffmanTree::HuffmanTree(string filepath) { // default constructor
    letterFreq(filepath + ".txt");
    buildTree();
}

// copy constructor

// move assignment constructor

// copy assignment operator

// move assignment operator

HuffmanTree::~HuffmanTree() { // destructor
    root = nullptr;
    std::cout << "Destroying tree." << std::endl;
}