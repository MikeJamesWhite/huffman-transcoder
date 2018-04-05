/**
 * HuffmanEncoder.cpp
 * 
 * Implementation file for the HuffmanTranscoder class
 * 
 * Author: Michael White
 * Date: 04/04/2018
 */

#include "huffman.h"
#include <vector>

using namespace WHTMIC023;

using std::string;
using std::endl;
using std::cout;
using std::vector;

void HuffmanTranscoder::encode(string inputFile, string outputFile) { // write out the encoded file as well as a header file which contains the code table
    buildCodeTable(inputFile);

    // write encoded file
    std::ofstream out = std::ofstream(outputFile);
    std::ifstream in = std::ifstream(inputFile);
    char c;
    string buffer = "";
    while (in.get(c)) {
        buffer += codeTable[c];
    }
    out << buffer;
    in.close();
    out.close();

    // write header file
    out.open(outputFile + ".hdr");
    out << std::to_string(codeTable.size()) << endl;
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

void HuffmanTranscoder::decode(string encodedFile, string outputFile){ // decodes a file using the code table
    ImportCodeTable(encodedFile + ".hdr");
    std::ofstream out = std::ofstream(outputFile);
    std::ifstream in = std::ifstream(encodedFile);
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

void HuffmanTranscoder::bitEncode(string inputFile, string outputFile) {
    buildCodeTable(inputFile);

    // read input file
    std::ifstream in = std::ifstream(inputFile);
    char c;
    string input = "";
    int charCount = 0; 

    while (in.get(c)) {
        input += codeTable[c];
        charCount++;
    }
    in.close();

    // pack bits
    int size = input.length() / 8;
    if ((input.length() % 8) > 0) 
        size++;

    float compression = float(size) / charCount;
    char buffer [size];

    int currentByte = 0;
    int currentBit = 0;
    char ch = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '1') {
            ch |= 1 << (7 - currentBit);
        }

        if (currentBit == 7) {
            currentBit = 0;
            buffer[currentByte] = ch;
            ch = 0;
            currentByte++;
        }
        else {
            currentBit++;
        }
    }
    
    if (currentBit != 0)
        buffer[currentByte] = ch;

    // write encoded file
    std::ofstream out = std::ofstream(outputFile, std::ios_base::binary);
    out << input.length();
    for (int i = 0; i < size; i++) {
        out << buffer[i];
    }
    out.close();

    // write header file
    out.open(outputFile + ".hdr");
    out << std::to_string(codeTable.size()) << endl;
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

    cout << "Uncompressed text length: " << std::to_string(charCount * 8) << " bits, packed into " << std::to_string(charCount) << " bytes." << endl;
    cout << "Compressed text length: " << std::to_string(input.length()) << " bits, packed into " << std::to_string(size) << " bytes." << endl;
    cout << "Compression ratio: " << std::to_string(compression) << endl;
}

void HuffmanTranscoder::bitDecode(string encodedFile, string outputFile) {
    ImportCodeTable(encodedFile + ".hdr");

    // read input
    std::ifstream in = std::ifstream(encodedFile, std::ios_base::binary);
    int numBits;
    in >> numBits;
    int numBytes = numBits / 8;
    if (numBits % 8 > 0)
        numBytes++;
    cout << "Number of bits to read: " << std::to_string(numBits) << endl;
    cout << "Number of bytes to read: " << std::to_string(numBytes) << endl;
    char input [numBytes];

    in.read(input, numBytes);
    in.close();

    // unpack bits
    string output = "";
    int currentByte = 0;
    int currentBit = 0;
    int bitsRead = 0;
    while (bitsRead < numBits) {
        string current = "";
        while (reverseTable.find(current) == reverseTable.end()) {
            if (input[currentByte] & 1 << (7 - currentBit)) {
                current += '1';
            }
            else {
                current += '0';
            }

            if (currentBit == 7) {
                currentBit = 0;
                currentByte++;
            }
            else {
                currentBit++;
            }
            bitsRead++;
        }
        cout << reverseTable[current] << ": " << current << endl;
        output += reverseTable[current];
        current = "";
    }

    // write decoded file
    std::ofstream out = std::ofstream(outputFile);
    for (int i = 0; i < output.length(); i++) {
        out << output[i];
    }

    out.close();
}

void HuffmanTranscoder::buildCodeTable(string input) { // creates a code table by building a huffman tree and then recursively traversing the tree, generating bitstrings
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
    int numSymbols;

    // get number of symbols
    std::getline(in, line);
    std::stringstream ss = std::stringstream(line);
    ss >> numSymbols;

    // build code table
    for (int i = 0; i < numSymbols; i++) {
        std::getline(in, line);
        if (line.substr(0,2) == "nl") {
            reverseTable[line.substr(3, line.length() -1)] = '\n';
        }
        else {
            reverseTable[line.substr(2, line.length() -1)] = line[0];
        }
    }
    in.close();
}