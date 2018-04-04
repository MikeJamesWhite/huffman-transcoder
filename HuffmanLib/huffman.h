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
            std::shared_ptr<HuffmanNode> left, right;
        
        public:
            HuffmanNode(char c, int i);

            HuffmanNode(std::shared_ptr<HuffmanNode> l, std::shared_ptr<HuffmanNode> r);

            HuffmanNode(const HuffmanNode & rhs);

            HuffmanNode(HuffmanNode && rhs);

            HuffmanNode & operator=(const HuffmanNode & rhs);

            HuffmanNode & operator=(HuffmanNode&& rhs);

            ~HuffmanNode();

            bool operator<(const HuffmanNode& other) const;
    };

    class HuffmanTree {
        private:
            std::shared_ptr<HuffmanNode> root;
            std::unordered_map<char, int> frequencies;

            void letterFreq (std::string filepath); // calculates the frequency of letters in a given file
        
            void buildTree (); // builds the huffman tree

            void encode(std::string inputFile, std::string outputFile); // write out the encoded
        
        public:
            HuffmanTree(std::string inputFile, std::string outputFile);

            ~HuffmanTree();

    };
}

#endif