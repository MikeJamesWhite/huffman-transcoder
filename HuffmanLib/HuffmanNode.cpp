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

class HuffmanNode {
    private:
        int freq;
        char letter;
        std::shared_ptr<HuffmanNode> left, right;
    
    public:
        HuffmanNode(char c, int i) { // default constructor
            letter = c;
            freq = i;
        }

        // copy constructor

        // move assignment constructor

        // copy assignment operator

        // move assignment operator

        ~HuffmanNode() { // destructor
            left = nullptr;
            right = nullptr;
        }

        bool operator<(const HuffmanNode & other) const { // '<' operator overload
            if (other.freq < freq) {
                return false;
            }
            else {
                return true;
            }
        }
};