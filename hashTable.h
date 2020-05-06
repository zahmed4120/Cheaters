//
// Created by zahme on 5/2/2020.
//

#ifndef CHEATERS_HASHTABLE_H
#define CHEATERS_HASHTABLE_H

#include <vector>
#include <cstring>
#include <string>
using namespace std;


class hashTable{
private:
    struct Node{
        int fileNum;
        Node *next;
    };

    struct cheatersNode{
        int score;
        int file1Number;
        int file2Number;
    };

    Node **simScores;

    int **cheatScores;

    int numberOfFiles;

    vector <cheatersNode> cheaters;

public:
    hashTable();

    hashTable(int numFiles);

    ~hashTable();

    int hashFunction(string fileString);

    void addNode(int fileNum, int index);

    void showHashTable();

    void showCheatingArray();

    void deleteNodes(int index);

    void cheatingArray();

    void setNumberOfFiles(int files);

    const int getNumberOfFiles();

    void findCheaters(int cheatCutoff);

    void sortCheaters();

    void showCheaters(vector <string> files);
};

#endif //CHEATERS_HASHTABLE_H
