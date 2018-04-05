CC=g++
TARGET=huffencode
FLAGS=-std=c++11 -I ./HuffmanLib -L ./HuffmanLib -lhuffman

.PHONY: clean

$(TARGET): driver.o
	$(CC) -o $(TARGET) driver.o $(FLAGS)

driver.o: driver.cpp
	make -C ./HuffmanLib/
	$(CC) -c -o driver.o driver.cpp $(FLAGS)

clean:
	rm -f *.o ./$(TARGET)
	make -C ./HuffmanLib clean

run: $(TARGET)
	export LD_LIBRARY_PATH=HuffmanLib/; \
	./huffencode testinput testoutput decoded
