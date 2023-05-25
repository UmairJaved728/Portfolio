OUTPUT=main
CC=g++
CFLAGS=-std=c++11 -Wall -Werror
SOURCES=main.cpp HashTable.cpp Song.cpp

all: $(OUTPUT)

$(OUTPUT): main.o HashTable.o Song.o
	$(CC) $(CFLAGS) $^ -o $(OUTPUT)

Tests: Tests.o HashTable.o Song.o
	$(CC) $(CFLAGS) $^ -o Tests

Tests.o: Tests.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

HashTable.o: HashTable.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

Song.o: Song.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o $(OUTPUT)
