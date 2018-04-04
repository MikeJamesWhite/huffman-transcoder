/**
 * HuffmanEncoder.cpp
 * 
 * Implementation file for the HuffmanEncoder class
 * 
 * Author: Michael White
 * Date: 04/04/2018
 */

#include "huffman.h"

using namespace WHTMIC023;

using std::string;

void HuffmanEncoder::encode(string inputFile, string outputFile){ // write out the encoded file as well as a header file which contains the code table


}

void HuffmanEncoder::buildCodeTable(string input, string output) { // builds the code table using a huffman tree
    HuffmanTree t = HuffmanTree(input, output);

}

void HuffmanEncoder::buildCodeTable(string filename) { // builds the code table from a header file


}

void HuffmanEncoder::decode(string encodedFile, string headerFile, string outputFile){ // decodes a file using the code table

} 