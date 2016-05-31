//
//  main.cpp
//  Project3B
//
//  Created by Gurtaj Khatra on 10/18/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#include <iostream>
#include "Heap.h"
#include "Hashtable.h";

#include <iostream>
#include "WordList.h"
#include "Grid.h"
#include "matrix.h"

#define MIN_WORD_LENGTH 5


//Return a string of letters to the left of a letter in a grid
//i = row, j = column, pMatrix = matrix of letters, numOfLetters = number of letters to get
string getLettersToLeft(int i, int j, const matrix<string>& pMatrix, int numOfLetters) {
    //Check for words to left
    string left = "";
    for (int k = 0; k < numOfLetters; k++) {
        int a = (j-k);
        int b = pMatrix.cols();
        left += pMatrix[i][(a%b+b)%b];
    }
    return left;
}
//Return a string of letters to the right of a letter in a grid
//i = row, j = column, pMatrix = matrix of letters, numOfLetters = number of letters to get
string getLettersToRight(int i, int j, const matrix<string>& pMatrix, int numOfLetters) {
    //Check for words to right
    string right = "";
    for (int k = 0; k < numOfLetters; k++) {
        int a = (j+k);
        int b = pMatrix.cols();
        right += pMatrix[i][(a%b+b)%b];
    }
    return right;
}
//Return a string of letters below a letter in a grid
//i = row, j = column, pMatrix = matrix of letters, numOfLetters = number of letters to get
string getLettersBelow(int i, int j, const matrix<string>& pMatrix, int numOfLetters) {
    //Check for words to below
    string below = "";
    for (int k = 0; k < numOfLetters; k++) {
        int a = (i+k);
        int b = pMatrix.cols();
        below += pMatrix[(a%b+b)%b][j];
    }
    return below;
}
//Return a string of letters above a letter in a grid
//i = row, j = column, pMatrix = matrix of letters, numOfLetters = number of letters to get
string getLettersAbove(int i, int j, const matrix<string>& pMatrix, int numOfLetters) {
    //Check for words to above
    string above = "";
    for (int k = 0; k < numOfLetters; k++) {
        int a = (i-k);
        int b = pMatrix.cols();
        above += pMatrix[(a%b+b)%b][j];
    }
    return above;
}
//Return a string of letters to the upper right of a letter in a grid
//i = row, j = column, pMatrix = matrix of letters, numOfLetters = number of letters to get
string getLettersAboveRight(int i, int j, const matrix<string>& pMatrix, int numOfLetters) {
    //Check for words to above
    string above = "";
    for (int k = 0; k < numOfLetters; k++) {
        int a = (i-k);
        int b = pMatrix.cols();
        int c = (j+k);
        int d = pMatrix.rows();
        above += pMatrix[(a%b+b)%b][(c%d+d)%d];
    }
    return above;
}
//Return a string of letters to the lower right of a letter in a grid
//i = row, j = column, pMatrix = matrix of letters, numOfLetters = number of letters to get
string getLettersBelowRight(int i, int j, const matrix<string>& pMatrix, int numOfLetters) {
    //Check for words to above
    string above = "";
    for (int k = 0; k < numOfLetters; k++) {
        int a = (i+k);
        int b = pMatrix.cols();
        int c = (j+k);
        int d = pMatrix.rows();
        above += pMatrix[(a%b+b)%b][(c%d+d)%d];
    }
    return above;
}
//Return a string of letters to the lower left of a letter in a grid
//i = row, j = column, pMatrix = matrix of letters, numOfLetters = number of letters to get
string getLettersBelowLeft(int i, int j, const matrix<string>& pMatrix, int numOfLetters) {
    //Check for words to above
    string above = "";
    for (int k = 0; k < numOfLetters; k++) {
        int a = (i+k);
        int b = pMatrix.cols();
        int c = (j-k);
        int d = pMatrix.rows();
        above += pMatrix[(a%b+b)%b][(c%d+d)%d];
    }
    return above;
}
//Return a string of letters to the upper left of a letter in a grid
//i = row, j = column, pMatrix = matrix of letters, numOfLetters = number of letters to get
string getLettersAboveLeft(int i, int j, const matrix<string>& pMatrix, int numOfLetters) {
    //Check for words to above
    string above = "";
    for (int k = 0; k < numOfLetters; k++) {
        int a = (i-k);
        int b = pMatrix.cols();
        int c = (j-k);
        int d = pMatrix.rows();
        above += pMatrix[(a%b+b)%b][(c%d+d)%d];
    }
    return above;
}


//Finds all the Words in a Grid
//list = list of words, puzzle = Grid consisting of the word search
void findMatches(WordList& list, Grid& puzzle) {
    //Find the max word size as well as load up the hash table
    Hashtable<string> wordHash = Hashtable<string>((int)list.words.size());
    int maxLengthWord = 0;
    for (int i = 0; i < list.words.size(); i++) {
        wordHash.addItem(list.words[i]);
        if (list.words[i].length() > maxLengthWord) {
            maxLengthWord = (int)list.words[i].length();
        }
    }
    vector<string> foundWords = {};
    //Puzzle matrix
    matrix<string> pMatrix = puzzle.grid;
    
    //Go through each char in the puzzle
    for (int i = 0; i < puzzle.height; i++) {
        for (int j = 0; j < puzzle.width; j++) {
            //Go through each possible word in the puzzle
            for (int k = MIN_WORD_LENGTH; k <= maxLengthWord; k++) {
                
                //Get potential words at this point by finding words in the wordlist
                //that start with a word of length MIN_WORD_LENGTH around this point
                string left = getLettersToLeft(i, j, pMatrix, k);
                if(wordHash.inList(left)) {
                    foundWords.push_back(left);
                }
                
                //Check for words to the right
                string right = getLettersToRight(i, j, pMatrix, k);
                if(wordHash.inList(right)) {
                    foundWords.push_back(right);
                }
                
                //Check for words below
                string below = getLettersBelow(i, j, pMatrix, k);
                if(wordHash.inList(below)) {
                    foundWords.push_back(below);
                }
                
                //Check for words above
                string above = getLettersAbove(i, j, pMatrix, k);
                if(wordHash.inList(above)) {
                    foundWords.push_back(above);
                }
                
                //Check for words diagonally from the above right
                string aboveRight = getLettersAboveRight(i, j, pMatrix, k);
                if(wordHash.inList(aboveRight)) {
                    foundWords.push_back(aboveRight);
                }
                
                //Check for words diagonally from the below right
                string belowRight = getLettersBelowRight(i, j, pMatrix, k);
                if(wordHash.inList(belowRight)) {
                    foundWords.push_back(belowRight);
                }
                
                //Check for words diagonally from the below left
                string belowLeft = getLettersBelowLeft(i, j, pMatrix, k);
                if(wordHash.inList(belowLeft)) {
                    foundWords.push_back(belowLeft);
                }
                
                //Check for words diagonally from the above left
                string aboveLeft = getLettersAboveLeft(i, j, pMatrix, k);
                if(wordHash.inList(aboveLeft)) {
                    foundWords.push_back(aboveLeft);
                }
            }
        }
    }
    
    cout << "Words Found: " << endl;
    for (string word:foundWords) {
        cout << word << endl;
    }
    
    
}

int main(int argc, const char * argv[]) {
    WordList list;
    
    
    //--------------------- PASTE YOUR PATH TO THE WORDLIST FILE HERE -----------------------
    list.wordListPath = "/Users/Gurtaj/Dropbox/College Work/Middler/Algorithms/Project3B/Project3B/Project3B/wordlist.txt";//|
    //---------------------------------------------------------------------------------------
    
    list.readWordList();
    cout << "Sorting the wordlist... " <<endl;
    clock_t startTime, endTime;
    startTime = clock();
    list.sortByHeapSort();
    float diff = clock()-startTime;
    float sortTime = (float) diff / CLOCKS_PER_SEC;
    cout << list << endl;
    cout << "Time taken to sort: " << sortTime << endl;
    
    
    Grid wordSearch;
    
    //-------------PASTE YOUR PATH TO THE GRID FILE HERE-----------------------------------------
    wordSearch.gridPath = "/Users/Gurtaj/Dropbox/College Work/Middler/Algorithms/Project3B/Project3B/Project3B/puzzle3_size50";//|
    //-------------------------------------------------------------------------------------------
    
    wordSearch.loadGrid();
    startTime = clock();
    findMatches(list, wordSearch);
    diff = clock()-startTime;
    float searchTime = (float) diff / CLOCKS_PER_SEC;
    cout << "Time taken to sort: " << sortTime << endl;
    cout << "Time taken to search: " << searchTime << endl;;
    cout << "Total time taken: " << sortTime+searchTime;
    
   
    system("pause");
    return 0;
}