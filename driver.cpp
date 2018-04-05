/**
 * driver.cpp
 * 
 * Driver program to run the Huffman Encoder
 * 
 * Author: Michael White
 * Date: 04/04/2018
 */

#include "huffman.h"
#include <iostream>

using namespace WHTMIC023;

using std::cout;
using std::endl;
using std::string;
using std::to_string;

int main(int argc, char * argv []) {
    string input = string(argv[1]);
    string output = string(argv[2]);
    string decodeOutput = string(argv[3]);
    cout << "Input file: " << input << endl;
    cout << "Output file: " << output << endl;
    cout << "Decode file: " << decodeOutput << endl;

    HuffmanTranscoder t = HuffmanTranscoder();
    t.encode(input, output);
    t.decode(output, decodeOutput);
}