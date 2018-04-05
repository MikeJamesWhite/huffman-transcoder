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
using std::endl;
using std::cout;

void HuffmanTranscoder::encode(string inputFile, string outputFile){ // write out the encoded file as well as a header file which contains the code table
    buildCodeTable(inputFile);

    // write encoded file
    std::ofstream out = std::ofstream(outputFile +".txt");
    std::ifstream in = std::ifstream(inputFile + ".txt");
    char c;
    while (in.get(c)) {
        out << codeTable[c];
    }
    in.close();
    out.close();

    // write header file
    out.open(outputFile + ".hdr");
    for (auto iter = codeTable.begin(); iter != codeTable.end(); iter++) {
        char c = iter -> first;
        string bitstring = iter -> second;
        if (c != '\n') {
            out << c << " " << bitstring << endl;
        }
        else {
            out << "nl " << bitstring << endl;
        }
    }
    out.close();
}

void HuffmanTranscoder::buildCodeTable(string input) { // builds the code table using a huffman tree
    HuffmanTree t = HuffmanTree(input);
    buildCodeTable(*t.root, "");
}

void HuffmanTranscoder::buildCodeTable(HuffmanNode n, string bitstring) { // recursively called to traverse the huffman tree
    if (n.getLetter() != '\0') {
        codeTable[n.getLetter()] = bitstring;
    }
    if (n.getLeft() != nullptr)
        buildCodeTable(*n.getLeft(), bitstring + "0");
    if (n.getRight() != nullptr)
        buildCodeTable(*n.getRight(), bitstring + "1");
}

void HuffmanTranscoder::ImportCodeTable(string filename) { // builds the code table from a header file
    reverseTable.clear();
    std::ifstream in = std::ifstream(filename);
    string line;

    while (std::getline(in, line)) {
        if (line.substr(0,2) == "nl") {
            reverseTable[line.substr(3, line.length() -1)] = '\n';
        }
        else {
            reverseTable[line.substr(2, line.length() -1)] = line[0];
        }
    }
    in.close();
}

void HuffmanTranscoder::decode(string encodedFile, string outputFile){ // decodes a file using the code table
    ImportCodeTable(encodedFile + ".hdr");
    std::ofstream out = std::ofstream(outputFile +".txt");
    std::ifstream in = std::ifstream(encodedFile + ".txt");
    string s = "";
    char c;

    while (in.get(c)) {
        s += c;
        if (reverseTable.find(s) != reverseTable.end()) {
            out.put(reverseTable[s]);
            s = "";
        }
    }
    in.close();
    out.close();   
}