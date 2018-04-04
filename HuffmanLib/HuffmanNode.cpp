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

        HuffmanNode(const HuffmanNode & rhs) { // copy constructor
            freq = rhs.freq;
            letter = rhs.letter;
            left = rhs.left;
            right = rhs.right;
        }

        HuffmanNode(HuffmanNode && rhs) { // move constructor
            freq = rhs.freq;
            letter = rhs.letter;
            left = std::move(rhs.left);
            right = std::move(rhs.right);

            rhs.freq = 0;
            rhs.letter = NULL;
        }

        HuffmanNode & operator=(const HuffmanNode & rhs) { // copy assignment operator
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

        HuffmanNode & operator=(HuffmanNode && rhs) { // move assignment operator
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
                rhs.letter = NULL;
                rhs.left = nullptr;
                rhs.right = nullptr;
            }
            return *this;
        }

        ~HuffmanNode() { // destructor
            freq = 0;
            letter = NULL;
            left = nullptr;
            right = nullptr;
        }

        bool operator<(const HuffmanNode & rhs) const { // '<' operator overload
            if (rhs.freq < freq) {
                return false;
            }
            else {
                return true;
            }
        }
};