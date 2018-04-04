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

using namespace WHTMIC023;
using std::string;

class Compare { // comparator for priority queue
    bool operator()(const HuffmanNode & a, const HuffmanNode & b) {
        return (a < b);
    }
};

class HuffmanTree {

    private:
        std::shared_ptr<HuffmanNode> root;
        std::unordered_map<char, int> frequencies;

        void letterFreq(string filepath) {
            frequencies.clear();
            std::ifstream in = std::ifstream(filepath);
            string line;
            while (std::getline(in, line)) {
                std::stringstream s = std::stringstream(line);
                char c;
                while (!s.eof()) {
                    s >> c;
                    if (frequencies.find(c) != frequencies.end()) {
                        frequencies[c]++;
                    }
                    else {
                        frequencies[c] = 1;
                    }
                }
            }
            std::cout << "Calculated frequencies!" << std::endl;
        }

        void buildTree() {
            std::priority_queue<HuffmanNode, Compare> nodes();
            
        }

    public:
        HuffmanTree(string filepath) { // default constructor
            letterFreq(filepath);
            buildTree();
        }

        // copy constructor

        // move assignment constructor

        // copy assignment operator

        // move assignment operator

        ~HuffmanTree() { // destructor

        }

};