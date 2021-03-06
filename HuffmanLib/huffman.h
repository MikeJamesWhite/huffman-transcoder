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

            bool operator>(const HuffmanNode& other) const;

            char getLetter() {
                return letter;
            }

            int getFrequency() {
                return freq;
            }

            const std::shared_ptr<HuffmanNode> getLeft() {
                return left;
            }
            
            const std::shared_ptr<HuffmanNode> getRight() {
                return right;
            }
    };

    class HuffmanTree {
        private:
            std::unordered_map<char, int> frequencies;

            void letterFreq (std::string filepath); // calculates the frequency of letters in a given file
        
            void buildTree (); // builds the huffman tree
        
        public:
            std::shared_ptr<HuffmanNode> root;

            HuffmanTree(std::string filepath); // constructor

            ~HuffmanTree(); // destructor

            HuffmanTree(const HuffmanTree & rhs); // copy constructor

            HuffmanTree(HuffmanTree && rhs); // move constructor

            HuffmanTree & operator=(const HuffmanTree & rhs); // copy assignment operator

            HuffmanTree & operator=(HuffmanTree && rhs); // move assignment operator

            const std::unordered_map<char, int> getFrequencies () {
                return frequencies;
            }
    };

    class HuffmanTranscoder {
        private:
            std::unordered_map<char, std::string> codeTable;
            std::unordered_map<std::string, char> reverseTable;

            void buildCodeTable(HuffmanNode n, std::string bitstring); // builds the code table using a huffman tree

        public:
            HuffmanTranscoder() {};

            void buildCodeTable(std::string input); // builds the code table using a huffman tree

            void ImportCodeTable(std::string filename); // imports the code table from a header file

            void encode(std::string inputFile, std::string outputFile); // write out the encoded file as well as a header file which contains the code table

            void decode(std::string encodedFile, std::string outputFile); // decode a file using the code table

            void bitEncode(std::string inputFile, std::string outputFile); // write out an encoded binary file as well as a header file

            void bitDecode(std::string encodedFile, std::string outputFile); // decode a binary file

            std::unordered_map<char, std::string> getCodeTable() {
                return codeTable;
            }

            std::unordered_map<std::string, char> getReverseTable() {
                return reverseTable;
            }

    };
}

#endif