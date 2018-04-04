CC=g++
TARGET=libhuffman.so
FLAGS=-fPIC -shared -std=c++11

$(TARGET): huffmanNode.o huffmanTree.o
	$(CC) -o $(TARGET) huffmanNode.o huffmanTree.o $(FLAGS)

huffmanTree.o: huffmanTree.cpp huffman.h
	$(CC) -c -o huffmanTree.o huffmanTree.cpp $(FLAGS)

huffmanNode.o: huffmanNode.cpp huffman.h
	$(CC) -c -o huffmanNode.o huffmanNode.cpp $(FLAGS)

clean:
	rm -f *.o *.so