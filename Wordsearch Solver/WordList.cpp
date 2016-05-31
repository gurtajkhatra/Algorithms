//
//  WordList.cpp
//  Project3a
//
//  Created by Gurtaj Khatra on 10/8/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#include "WordList.h"
#include <iostream>

//Reads all the words line by line from a file specified in wordListPath
void WordList::readWordList() {
    string line;
    ifstream wordlist(wordListPath);
    while ( getline (wordlist,line) )
    {
        words.push_back(line);

    }
}


//Sorts the word vector using insertion sort
void WordList::sortByInsertion() {
    int sizeOfWords = (int)words.size();
    for (int i = 2; i < sizeOfWords; i++) {
        for (int k = i; k > 0; k--) {
            string str2 = words[k];
            string str1 = words[k-1];
            if (str1.compare(str2) > 0) {
                string temp = str1;
                words[k-1] = str2;
                words[k] = str1;
            }
            else {
                break;
            }
        }
    }
}

//Sorts the word vector using quick sort
void WordList::sortByQuickSort() {
    sortByQuickSort(0, (int)words.size()-1);
}

//Sorts the word vector using insertion sort from a particular index to another one
void WordList::sortByQuickSort(int leftIndex, int rightIndex) {
    int lIndex = leftIndex;
    int rIndex = rightIndex;
    string temp = "p";
    string pivot = words[(lIndex+rIndex)/2];
    
    while (lIndex <= rIndex) {
        while (words[lIndex].compare(pivot) < 0) {
            lIndex++;
        }
        while (words[rIndex].compare(pivot) > 0) {
            rIndex--;
        }
        if (lIndex <= rIndex) {
            temp = words[lIndex];
            words[lIndex] = words[rIndex];
            words[rIndex] = temp;
            lIndex++;
            rIndex--;
        }
    }
    
    if (leftIndex < rIndex) {
        sortByQuickSort(leftIndex, rIndex);
    }
    if (lIndex < rightIndex) {
        sortByQuickSort(lIndex, rightIndex);
    }
}


//Helper function for merge sorting
vector<string> mergeHelper(vector<string> &leftSide, vector<string> &rightSide, vector<string> &v) {
    vector<string> result;
    clock_t startTime, endTime;
    startTime = clock();
    int rightSideSize = (int)rightSide.size();
    int rightSideIndex = 0;
    int leftSideSize = (int)leftSide.size();
    int leftSideIndex = 0;
    while (leftSideSize > leftSideIndex && rightSideSize > rightSideIndex) {
        if (leftSide[leftSideIndex].compare(rightSide[rightSideIndex]) < 0) {
            result.push_back(leftSide[leftSideIndex]);
            //leftSide.erase(leftSide.begin());
            leftSideIndex++;
        }
        else {
            result.push_back(rightSide[rightSideIndex]);
            rightSideIndex++;
        }
    }
    while (leftSideSize > leftSideIndex) {
        result.push_back(leftSide[leftSideIndex]);
        leftSideIndex++;
    }
    while (rightSideSize > rightSideIndex) {
        result.push_back(rightSide[rightSideIndex]);
        rightSideIndex++;
        
    }
    v = result;
    return v;
}

//Sorts any vector of strings by using merge sort
vector<string> sortVectorByMergeSort(vector<string> &v) {
    if (v.size() == 1) {
        return v;
    }
    
    vector<string>::iterator middleOfV = v.begin() + (v.size()/2);
    vector<string> leftSide(v.begin(), middleOfV);
    vector<string> rightSide(middleOfV, v.end());
    
    leftSide = sortVectorByMergeSort(leftSide);
    rightSide = sortVectorByMergeSort(rightSide);
    
    return mergeHelper(leftSide,rightSide, v);
}

//Sorts the words vector using merge sort
void WordList::sortByMergeSort() {
    words = sortVectorByMergeSort(words);
}

void WordList::sortByHeapSort() {
    Heap<string> wordHeap;
    wordHeap.data = words;
    wordHeap.heapsort();
    words = wordHeap.data;
}

//Searches though any vector of strings to find a word
//Returns true if it contains it, false if it doesn't
bool binarySearchHelper(string word, vector<string>&v) {
    int start = 0;
    int end = (int)v.size()-1;
    int middle;
    while (start <= end) {
        middle = start + ((end-start)/2);
        if (word.compare(v[middle]) == 0) {
            return true;
        }
        else if (word.compare(v[middle]) < 0) {
            end = middle-1;
        }
        else if (word.compare(v[middle]) > 0) {
            start = middle+1;
        }
    }
    return false;
}

//Performs a binary search on the word vector to find a string
//Returns true if it contains it, false if it doesn't
bool WordList::searchIfInList(string word) {
    return binarySearchHelper(word, words);
}

//Performs a binary seach on the words vector to find all words that begin with
//a particular string (begining).
vector<string> WordList::findWordsThatStartWith(string begining) {
    int start = 0;
    int end = (int)words.size()-1;
    int middle;
    vector<string>potentialWords = {};
    int length = (int)begining.length();
    while (start <= end) {
        middle = start + ((end-start)/2);
        //Check if begining is the same
        if (begining.compare(words[middle].substr(0,length)) == 0) {
            potentialWords.push_back(words[middle]);
            int tempMiddle = middle;
            tempMiddle++;
            while (begining.compare(words[tempMiddle].substr(0,length)) == 0) {
                potentialWords.push_back(words[tempMiddle]);
                tempMiddle++;
            }
            middle--;
            while (begining.compare(words[middle].substr(0,length)) == 0) {
                potentialWords.push_back(words[middle]);
                middle--;
            }
            break;
        }
        else if (begining.compare(words[middle]) < 0) {
            end = middle-1;
        }
        else if (begining.compare(words[middle]) > 0) {
            start = middle+1;
        }
    }
    return potentialWords;
}

int WordList::hashString(string str) {
    int index = 0;
    for (int i=0; i<str.length(); i++)
        index += (int) str[i];
    index = index%(words.size());
    return index;
}

//Operator overloading the <<
ostream& operator<<(ostream& out,const WordList& wl) {
    for (int i = 0; i < wl.words.size(); i++) {
        cout << wl.words[i] << endl;
    }
    return out;
}