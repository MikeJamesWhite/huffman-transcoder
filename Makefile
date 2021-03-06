CC=g++
TARGET=huffencode
FLAGS=-std=c++11 -I ./HuffmanLib -L ./HuffmanLib -lhuffman

.PHONY: clean

$(TARGET): driver.o
	$(CC) -o $(TARGET) driver.o $(FLAGS)

driver.o: driver.cpp
	make -C ./HuffmanLib/
	$(CC) -c -o driver.o driver.cpp $(FLAGS)

tests: tests.cpp
	make -C ./HuffmanLib/
	$(CC) -o testRunner tests.cpp $(FLAGS)
	export LD_LIBRARY_PATH=HuffmanLib/; \
	./testRunner -s

clean:
	rm -f *.o ./$(TARGET) ./testRunner
	make -C ./HuffmanLib clean

run: $(TARGET)
	export LD_LIBRARY_PATH=HuffmanLib/; \
	./huffencode testinput.txt testoutput

encode: $(TARGET)
	export LD_LIBRARY_PATH=HuffmanLib/; \
	./huffencode testinput.txt testoutput -e

decode: $(TARGET)
	export LD_LIBRARY_PATH=HuffmanLib/; \
	./huffencode testoutput decoded.txt -d

bitEncode: $(TARGET)
	export LD_LIBRARY_PATH=HuffmanLib/; \
	./huffencode testinput.txt testoutput -be

bitDecode: $(TARGET)
	export LD_LIBRARY_PATH=HuffmanLib/; \
	./huffencode testoutput decoded.txt -bd