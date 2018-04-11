/**
 * tests.cpp
 * 
 * Unit tests for the Huffman Transcoder program
 * 
 * Author: Michael White
 * Date: 10/04/2018
 */

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "huffman.h"

using namespace WHTMIC023;
using namespace std;

// HUFFMAN NODE TESTING
TEST_CASE("Huffman Node Special Member functions execute correctly", "[huffman_node]") {

    char c = 'a';
    int i = 7;
    HuffmanNode node(c, i);

    SECTION("Default Constructor") {
        REQUIRE(node.getLetter() == c);
        REQUIRE(node.getFrequency() == i);
    }

    SECTION("Parent Constructor") {
        char c2 = 'b';
        int i2 = 8;
        HuffmanNode node2(c2, i2);
        HuffmanNode parent(node, node2);
        HuffmanNode l = *parent.getLeft().get();
        HuffmanNode r = *parent.getRight().get();
        REQUIRE(l.getFrequency() == i);
        REQUIRE(l.getLetter() == c);
        REQUIRE(r.getFrequency() == i2);
        REQUIRE(r.getLetter() == c2);
        REQUIRE(parent.getFrequency() == (i + i2));
        REQUIRE(parent.getLetter() == '\0');
    }

    SECTION("Destructor") {
        char c2 = 'b';
        int i2 = 8;
        HuffmanNode node2(c2, i2);
        HuffmanNode parent(node, node2);
        parent.~HuffmanNode();
        REQUIRE(parent.getFrequency() == 0);
        REQUIRE(parent.getLetter() == '\0');
        REQUIRE(parent.getLeft() == nullptr);
        REQUIRE(parent.getRight() == nullptr);
    }

    SECTION("Copy Constructor") {
        HuffmanNode node2(node);
        REQUIRE(node2.getFrequency() == node.getFrequency());
        REQUIRE(node2.getLetter() == node.getLetter());
        REQUIRE(node2.getLeft() == node.getLeft());
        REQUIRE(node2.getRight() == node.getRight());
    }

    SECTION("Move Constructor") {
        HuffmanNode node2(move(node));
        REQUIRE(node2.getLetter() == c);
        REQUIRE(node2.getFrequency() == i);
        REQUIRE(node.getLetter() == '\0');
        REQUIRE(node.getFrequency() == 0);
    }

    SECTION("Copy Assignment Operator") {
        HuffmanNode node2 = node;
        REQUIRE(node2.getFrequency() == node.getFrequency());
        REQUIRE(node2.getLetter() == node.getLetter());
        REQUIRE(node2.getLeft() == node.getLeft());
        REQUIRE(node2.getRight() == node.getRight());
    }

    SECTION("Move Assignment Operator") {
        HuffmanNode node2 = move(node);
        REQUIRE(node2.getLetter() == c);
        REQUIRE(node2.getFrequency() == i);
        REQUIRE(node.getLetter() == '\0');
        REQUIRE(node.getFrequency() == 0);
    }

}

TEST_CASE("Huffman Node comparison operator executes correctly", "[huffman_node]") {
    char c = 'a';
    int i = 7;
    HuffmanNode node(c, i);

    char c2 = 'b';
    int i2 = 8;
    HuffmanNode node2(c2, i2);

    REQUIRE((node > node2) == false);
}

// HUFFMAN TREE TESTING
TEST_CASE("Huffman Tree methods execute as expected", "[huffman_tree]") {

    SECTION("Huffman Tree generates the correct letter frequency table") {
    
        HuffmanTree t ("./test_docs/unit_testing_input.txt");

        auto frequencies = t.getFrequencies();
        REQUIRE(frequencies[' '] == 7);
        REQUIRE(frequencies['a'] == 4);
        REQUIRE(frequencies['e'] == 4);
        REQUIRE(frequencies['f'] == 3);
        REQUIRE(frequencies['h'] == 2);
        REQUIRE(frequencies['i'] == 2);
        REQUIRE(frequencies['m'] == 2);
        REQUIRE(frequencies['n'] == 2);
        REQUIRE(frequencies['s'] == 2);
        REQUIRE(frequencies['t'] == 2);
        REQUIRE(frequencies['l'] == 1);
        REQUIRE(frequencies['o'] == 1);
        REQUIRE(frequencies['p'] == 1);
        REQUIRE(frequencies['r'] == 1);
        REQUIRE(frequencies['u'] == 1);
        REQUIRE(frequencies['x'] == 1);
        REQUIRE(frequencies['\n'] == 1);
    }

    SECTION("Huffman Tree builds the correct tree", "[huffman_tree]") {
        HuffmanTree t ("./test_docs/unit_testing_input2.txt");
        REQUIRE((*t.root).getFrequency() == 10);
        HuffmanNode n1 = *(*t.root).getLeft();
        HuffmanNode n2 = *(*t.root).getRight();
        HuffmanNode n3 = *n2.getLeft();
        HuffmanNode n4 = *n2.getRight();
        HuffmanNode n5 = *n4.getLeft();
        HuffmanNode n6 = *n4.getRight();

        REQUIRE(n1.getFrequency() == 4);
        REQUIRE(n1.getLetter() == 'a');
        REQUIRE(n2.getFrequency() == 6);
        REQUIRE(n2.getLetter() == '\0');
        REQUIRE(n3.getFrequency() == 3);
        REQUIRE(n3.getLetter() == 'b');
        REQUIRE(n4.getFrequency() == 3);
        REQUIRE(n4.getLetter() == '\0');
        REQUIRE(n5.getFrequency() == 1);
        REQUIRE(n5.getLetter() == '\n');
        REQUIRE(n6.getFrequency() == 2);
        REQUIRE(n6.getLetter() == ' ');

    /**
     * EXPECTED REPRESENTATION
     * 
     *             10:null
     *            /       \
     *         4:'a'      6:null
     *                    /     \
     *                 3:'b'    3:null
     *                         /     \
     *                      1:'\n'   2:' '
     */
    }
}

TEST_CASE("Huffman Tree special member functions operate as expected", "[huffman_tree]") {
    
    HuffmanTree t ("./test_docs/unit_testing_input.txt");

    SECTION("Default Constructor") {
        REQUIRE( (*t.root).getFrequency() == 37);
    }

    SECTION("Destructor") {
        t.~HuffmanTree();
        REQUIRE(t.root == nullptr);
    }

    SECTION("Copy Constructor") {
        HuffmanTree t2(t);
        REQUIRE(t2.root.get() == t.root.get());
    }

    SECTION("Copy Assignment Operator") {
        HuffmanTree t2 = t;
        REQUIRE(t2.root.get() == t.root.get());
    }

    SECTION("Move Constructor") {
        HuffmanNode* r = t.root.get();

        HuffmanTree t2(move(t));
        REQUIRE(t2.root.get() == r);

        REQUIRE(t.root == nullptr);
        REQUIRE(t.getFrequencies().empty());
    }

    SECTION("Move Assignment Operator") {
        HuffmanNode* r = t.root.get();

        HuffmanTree t2 = move(t);
        REQUIRE(t2.root.get() == r);
    
        REQUIRE(t.root == nullptr);
        REQUIRE(t.getFrequencies().empty());
    }
}

// HUFFMAN TRANSCODER TESTING -> INCLUDES TESTING OF EXTENSION TASK (BITSTREAM OPERATIONS) 
TEST_CASE("Huffman Transcoder builds the correct code table", "[huffman_transcoder]") {
    HuffmanTranscoder t = HuffmanTranscoder();
    t.buildCodeTable("./test_docs/unit_testing_input.txt");
    auto codeTable = t.getCodeTable();
    REQUIRE(codeTable[' '] == "111");
    REQUIRE(codeTable['h'] == "0101");
    REQUIRE(codeTable['i'] == "11001");
    REQUIRE(codeTable['l'] == "10001");
    REQUIRE(codeTable.size() == 17);
}

TEST_CASE("Huffman Transcoder imports the correct code table", "[huffman_transcoder]") {
    HuffmanTranscoder t = HuffmanTranscoder();
    t.ImportCodeTable("./test_docs/unit_testing_expectedHeader.hdr");
    auto reverseTable = t.getReverseTable();
    REQUIRE(reverseTable["111"] == ' ');
    REQUIRE(reverseTable["0101"] == 'h');
    REQUIRE(reverseTable["11001"] == 'i');
    REQUIRE(reverseTable["10001"] == 'l');
    REQUIRE(reverseTable.size() == 17);
}

TEST_CASE("Huffman Transcoder encodes correctly", "[huffman_transcoder]") {
    HuffmanTranscoder t = HuffmanTranscoder();
    t.encode("./test_docs/unit_testing_input2.txt", "./test_docs/unit_testing_output_encoded");

    ifstream expected("./test_docs/unit_testing_expected");
    ifstream generated("./test_docs/unit_testing_output_encoded");
    string s = "";
    string s2 = "";
    getline(expected, s);
    getline(generated, s2);

    expected.close();
    generated.close();

    REQUIRE(s == s2);
}

TEST_CASE("Huffman Transcoder decodes correctly", "[huffman_transcoder]") {
    HuffmanTranscoder t = HuffmanTranscoder();
    t.decode("./test_docs/unit_testing_expected", "./test_docs/unit_testing_output_decoded");

    ifstream expected("./test_docs/unit_testing_input2.txt");
    ifstream generated("./test_docs/unit_testing_output_decoded");
    string s = "";
    string s2 = "";
    getline(expected, s);
    getline(generated, s2);

    expected.close();
    generated.close();

    REQUIRE(s == s2);
}

TEST_CASE("Huffman Transcoder encodes to and from bitstream correctly", "[huffman_transcoder]") {
    
    HuffmanTranscoder encoder = HuffmanTranscoder();
    encoder.bitEncode("./test_docs/unit_testing_input3.txt", "./test_docs/unit_testing_output_binEncoded");

    HuffmanTranscoder decoder = HuffmanTranscoder();
    decoder.bitDecode("./test_docs/unit_testing_output_binEncoded", "./test_docs/unit_testing_output_binDecoded");

    ifstream expected("./test_docs/unit_testing_input3.txt");
    ifstream generated("./test_docs/unit_testing_output_binDecoded");
    string s = "";
    string s2 = "";
    bool areTheSame = true;

    while (!expected.eof() && !generated.eof()) {
        getline(expected, s);
        getline(generated, s2);
        if (s != s2) {
            cout << s << endl;
            cout << s2 << endl;
            areTheSame = false;
            break;
        }
    }
    if (!(expected.eof() && generated.eof())) {
        areTheSame = false; 
    }

    expected.close();
    generated.close();

    REQUIRE(areTheSame);
}