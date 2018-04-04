/**
 * huffmanNode.cpp
 * 
 * Implementation file for the HuffmanNode class
 * 
 * Author: Michael White
 * Date: 04/04/2018
 */

#include "huffman.h"
#include <memory>

using namespace WHTMIC023;

class HuffmanNode {
    int freq;
    char letter;
    std::shared_ptr<HuffmanNode> left, right;
    
    public:


};