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
        std::cout << "creating a node" << endl;
}

HuffmanNode::HuffmanNode(const HuffmanNode& l, const HuffmanNode& r) { // parent constructor
    letter = '\0';
    freq = l.freq + r.freq;
    left = make_shared<HuffmanNode>(l);
    right = make_shared<HuffmanNode>(r); 
    std::cout << "creating a parent node" << endl;
}

HuffmanNode::HuffmanNode(const HuffmanNode & rhs) { // copy constructor
    freq = rhs.freq;
    letter = rhs.letter;
    left = rhs.left;
    right = rhs.right;
    //std::cout << "copying a node" << endl;
}

HuffmanNode::HuffmanNode(HuffmanNode && rhs) { // move constructor
    freq = rhs.freq;
    letter = rhs.letter;
    left = std::move(rhs.left);
    right = std::move(rhs.right);

    rhs.freq = 0;
    rhs.letter = '\0';
    //std::cout << "moving a node" << endl;
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
    //std::cout << "copying a node" << endl;
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
    //std::cout << "moving a node" << endl;
    return *this;
}

HuffmanNode::~HuffmanNode() { // destructor
    freq = 0;
    letter = '\0';
    left = nullptr;
    right = nullptr;
    //cout << "Destroying a node" << endl;
}

bool HuffmanNode::operator<(const HuffmanNode & rhs) const { // '<' operator overload
    if (rhs.freq < freq) {
        return false;
    }
    else {
        return true;
    }
}