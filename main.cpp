#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <cstring>
#include <stdlib.h>
#include "hashTable.h"

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


int main(int argc, char* argv [])
{

    int numWords = atoi(argv[2]);
    //int numWords = 6;
    int cheatingScore = atoi(argv[3]);
    //int cheatingScore = 200;

    string dir = string(argv[1]);
    //string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir,files);

    files.erase(files.begin(), files.begin() + 2);
    for (unsigned int i = 0; i < files.size();i++) {
        cout << i << files[i] << endl;
    }

    hashTable t(files.size());

    for(int index = 0; index < files.size(); index ++){
        vector<string> words;
        ifstream file;
        string fileName;
        fileName.append(dir);
        fileName.append("/");
        fileName.append(files[index]);
        file.open(fileName.c_str());
        string s;
        file >> s;

        while(file){
            while(words.size() < numWords){
                words.push_back(s);
                file >> s;
            }
            string temp;
            for(int i = 0; i < numWords; i ++){
                temp.append(words[i]);
            }
            for(int j = 0; j < temp.size(); j ++){
                if((temp[j] >= 48 && temp[j] <= 57) || (temp[j] >= 65 && temp[j] <= 90) || (temp[j] >= 97 && temp[j] <= 122)){
                    temp[j] = tolower(temp[j]);
                }
                else{
                    temp.erase(temp.begin() + j);
                    j = j - 1;
                }
            }
            t.addNode(index, t.hashFunction(temp));
            words.erase(words.begin());
        }

    }

    cout << endl;
    t.cheatingArray();
    t.findCheaters(cheatingScore);
    t.showCheaters(files);
    cout << endl;

    cout << "Program Done" << endl;
    return 0;
}
