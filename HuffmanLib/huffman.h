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

            HuffmanNode(const HuffmanNode& l, const HuffmanNode& r);

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
        
        public:
            HuffmanTree(std::string inputFile, std::string outputFile);

            ~HuffmanTree();

    };

    class HuffmanEncoder {
        private:
            std::unordered_map<char, std::string> codeTable;

        public:
            void encode(std::string inputFile, std::string outputFile); // write out the encoded file as well as a header file which contains the code table

            void buildCodeTable(std::string input, std::string output); // builds the code table using a huffman tree

            void buildCodeTable(std::string filename); // builds the code table from a header file

            void decode(std::string encodedFile, std::string headerFile, std::string outputFile); // decodes a file using the code table
    };
}

#endif