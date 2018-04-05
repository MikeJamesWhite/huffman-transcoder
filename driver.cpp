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
    cout << "Input file: " << input << endl;
    cout << "Output file: " << output << endl;

    HuffmanTranscoder t = HuffmanTranscoder();

    if (argc <= 3) { // assume encode if no additional argument
        cout << "Encoding input file to output." << endl;
        t.encode(input, output);
    }
    else if (string(argv[3]) == "-e") { // -e option explicitly runs encode
        cout << "Encoding input file to output." << endl;
        t.encode(input, output);
    }
    else if (string(argv[3]) == "-d") { // -d option runs decode
        cout << "Decoding input file to output." << endl;
        t.decode(input, output);
    }
    else if (string(argv[3]) == "-be") { // -be option runs bitEncode
        cout << "Encoding input file to binary output." << endl;
        t.bitEncode(input, output);
    }
    else if (string(argv[3]) == "-bd") { // -bd option runs bitDecode
        cout << "Decoding binary input file to output." << endl;
        t.bitDecode(input, output);
    }
}