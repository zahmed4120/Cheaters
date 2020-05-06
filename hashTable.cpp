//
// Created by zahme on 5/2/2020.
//

#include "hashTable.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

hashTable::hashTable(){
    simScores = new Node*[100000];
    for(int i = 0; i < 100000; i++){
        simScores[i] = new Node;
        simScores[i] -> fileNum = -1;
        simScores[i] -> next = nullptr;
    }

    cheatScores = new int*[100000];
    for(int j = 0; j < 100000; j++){
        cheatScores[j] = new int[100000];
    }

    setNumberOfFiles(100000);

}

hashTable::hashTable(int numFiles){
    simScores = new Node*[100000];
    for(int i = 0; i < 100000; i++){
        simScores[i] = new Node;
        simScores[i] -> fileNum = -1;
        simScores[i] -> next = nullptr;
    }

    cheatScores = new int*[numFiles];
    for(int j = 0; j < numFiles; j ++){
        cheatScores[j] = new int[numFiles];
    }

    setNumberOfFiles(numFiles);

}


hashTable::~hashTable(){
    for(int i = 0; i < 100000; i ++){
        deleteNodes(i);
        delete simScores[i];
    }
    delete [] simScores;

    for(int j = 0; j < getNumberOfFiles(); j ++){
        delete [] cheatScores[j];
    }
    delete [] cheatScores;

    cout << "Destructor Finished" << endl;

}

void hashTable::deleteNodes(int index){
    Node *current;
    Node *prev;
    current = simScores[index] -> next;
    while(current != nullptr){
        prev = current;
        current = current -> next;
        delete prev;
    }
}

int hashTable::hashFunction(string fileString){
    int sum = 0;
    for(string::iterator i = fileString.begin(); i != fileString.end(); i ++){
        sum = sum + *i;
    }
    return (sum * fileString.length()) % 100000;

}

void hashTable::addNode(int fileNum, int index){
    Node *temp = new Node;
    temp -> fileNum = fileNum;
    temp -> next = nullptr;

    if(simScores[index] == nullptr){
        simScores[index] -> next = temp;
    }
    else{
        Node *temp2;
        temp2 = simScores[index] -> next;
        temp -> next = temp2;
        simScores[index] -> next = temp;
    }
}

void hashTable::showHashTable(){
    for(int i = 0; i < 100000; i ++){
        Node *temp = simScores[i];
        while(temp != nullptr){
            cout << temp -> fileNum << " ";
            temp = temp -> next;
        }
        cout << endl;
    }
}

void hashTable::showCheatingArray(){
    for(int i = 0; i < getNumberOfFiles(); i ++){
        for(int j = 0; j < getNumberOfFiles(); j ++){
            cout << cheatScores[i][j] << " ";
        }
        cout << endl;
    }
}

void hashTable::cheatingArray(){
    for(int i = 0; i < 100000; i ++){
        Node *temp;
        temp = simScores[i] -> next;
        if(temp != nullptr){
            Node *temp2;
            temp2 = temp -> next;
            while(temp2 != nullptr){
                if(temp -> fileNum != temp2 -> fileNum){
                    cheatScores[temp -> fileNum][temp2 -> fileNum] = cheatScores[temp -> fileNum][temp2 -> fileNum] + 1;
                }
                temp2 = temp2 -> next;
            }
        }
    }
}

void hashTable::setNumberOfFiles(int files){
    numberOfFiles = files;
}

const int hashTable::getNumberOfFiles(){
    return numberOfFiles;
}

void hashTable::findCheaters(int cheatCutoff){
    for(int i = 0; i < getNumberOfFiles(); i++){
        for(int j = 0; j < getNumberOfFiles(); j ++){
            if(cheatScores[i][j] >= cheatCutoff){
                cheatersNode temp;
                temp.score = cheatScores[i][j];
                temp.file1Number = i;
                temp.file2Number = j;
                cheaters.push_back(temp);
            }
        }
    }
}

void hashTable::sortCheaters(){
    vector <cheatersNode> temp;

    while(cheaters.size() > 0){
        int maxScore = 0;
        int maxIndex = 0;
        for(int i = 0; i < cheaters.size(); i ++){
            if(cheaters[i].score > maxScore){
                maxScore = cheaters[i].score;
                maxIndex = i;
            }
        }
        temp.push_back(cheaters[maxIndex]);
        cheaters.erase(cheaters.begin() + maxIndex, cheaters.begin() + maxIndex + 1);
    }
    cheaters.swap(temp);
}

void hashTable::showCheaters(vector <string> files){
    sortCheaters();
    for(int i = 0; i < cheaters.size(); i++){
        cout << cheaters[i].score << ": filename:" << files[cheaters[i].file1Number] << ", filename:" << files[cheaters[i].file2Number] << endl;
    }
}

