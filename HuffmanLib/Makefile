CC=g++
TARGET=libhuffman.so
FLAGS=-fPIC -shared -std=c++11

$(TARGET): HuffmanNode.o HuffmanTree.o
	$(CC) -o $(TARGET) HuffmanNode.o HuffmanTree.o $(FLAGS)

HuffmanTree.o: HuffmanTree.cpp huffman.h
	$(CC) -c -o HuffmanTree.o HuffmanTree.cpp $(FLAGS)

HuffmanNode.o: HuffmanNode.cpp huffman.h
	$(CC) -c -o HuffmanNode.o HuffmanNode.cpp $(FLAGS)

clean:
	rm -f *.o *.so