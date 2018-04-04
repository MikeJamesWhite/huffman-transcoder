#ifndef HUFFMAN
#define HUFFMAN

#include <string>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>

namespace WHTMIC023 {

    class HuffmanNode {
        private:
            char letter;
            int freq;
        
        public:
            bool operator<(const HuffmanNode& other) const;
    };

    class HuffmanTree {
        private:
            std::shared_ptr<HuffmanNode> root;
            std::unordered_map<char, int> frequencies;

            void letterFreq (std::string filepath); // calculates the frequency of letters in a given file
        
            void buildTree (); // builds the huffman tree

        public:

    };
}

#endif