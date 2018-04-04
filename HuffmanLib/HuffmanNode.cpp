/**
 * huffmanNode.cpp
 * 
 * Implementation file for the HuffmanNode class
 * 
 * Author: Michael White
 * Date: 04/04/2018
 */

#include "huffman.h"

using namespace WHTMIC023;
using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::endl;

HuffmanNode::HuffmanNode(char c, int i) { // default constructor
        letter = c;
        freq = i;
        std::cout << "creating a node";
}

HuffmanNode::HuffmanNode(shared_ptr<HuffmanNode> l, shared_ptr<HuffmanNode> r) { // parent constructor
    letter = '\0';
    freq = l -> freq + r ->freq;
    left = std::move(l);
    right = std::move(r);
    std::cout << "creating a parent node";
}

HuffmanNode::HuffmanNode(const HuffmanNode & rhs) { // copy constructor
    freq = rhs.freq;
    letter = rhs.letter;
    left = rhs.left;
    right = rhs.right;
}

HuffmanNode::HuffmanNode(HuffmanNode && rhs) { // move constructor
    freq = rhs.freq;
    letter = rhs.letter;
    left = std::move(rhs.left);
    right = std::move(rhs.right);

    rhs.freq = 0;
    rhs.letter = '\0';
}

HuffmanNode & HuffmanNode::operator=(const HuffmanNode & rhs) { // copy assignment operator
    if (this != &rhs) {
        left = nullptr;
        right = nullptr;

        freq = rhs.freq;
        letter = rhs.letter;
        left = rhs.left;
        right = rhs.right;
    }
    return *this;
}

HuffmanNode & HuffmanNode::operator=(HuffmanNode && rhs) { // move assignment operator
    if (this != &rhs) {
        // release current resources
        left = nullptr;
        right = nullptr;

        // move rhs resources
        freq = rhs.freq;
        letter = rhs.letter;
        left = rhs.left;
        right = rhs.right;

        // release resources from rhs
        rhs.freq = 0;
        rhs.letter = '\0';
        rhs.left = nullptr;
        rhs.right = nullptr;
        }
    return *this;
}

HuffmanNode::~HuffmanNode() { // destructor
    freq = 0;
    letter = '\0';
    left = nullptr;
    right = nullptr;
    cout << "Destroying a node" << endl;
}

bool HuffmanNode::operator<(const HuffmanNode & rhs) const { // '<' operator overload
    if (rhs.freq < freq) {
        return false;
    }
    else {
        return true;
    }
}