driver: main.o hashTable.o
	g++ -std=c++11 -o plagiarismCatcher main.o hashTable.o
plagiarismCatcher: main.cpp hashTable.h
	g++ -std=c++11 -c main.cpp
hashTable.o: hashTable.cpp hashTable.h
	g++ -std=c++11 -c hashTable.cpp
