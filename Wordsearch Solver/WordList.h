//
//  WordList.h
//  Project3a
//
//  Created by Gurtaj Khatra on 10/8/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#ifndef WordList_h
#define WordList_h

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Heap.h"
using namespace std;

class WordList {
public:
    //File path of the word list
    string wordListPath;
    //Vector containing all of the possible words
    vector <string> words;
    
    void readWordList();
    void sortByInsertion();
    void sortByQuickSort(int left, int right);
    void sortByQuickSort();
    void sortByMergeSort();
    void sortByHeapSort();
    bool searchIfInList(string word);
    vector<string> findWordsThatStartWith(string begining);
    int hashString(string str);
    friend ostream& operator<<(ostream& out,const WordList& wl);
};


#endif /* WordList_h */
