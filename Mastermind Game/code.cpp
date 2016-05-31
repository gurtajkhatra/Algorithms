//
//  code.cpp
//  Project1a
//
//  Created by Gurtaj Khatra on 9/19/15.
//  Implementaion file for a code object

#include "code.h"
#include <iostream>
#include <math.h>

//Helper function to generate a random number from [0,10)
int randomNumberBetweenZeroAndTen() {
    return (rand() % (int)(10));
}

//Helper function to search through a vector of integers
//to see if it contains an integer that is passed as an argument.
bool vectorContainsInt(std::vector<int> vector, int seachFor) {
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i] == seachFor) {
            return true;
        }
    }
    return false;
}

//Empty constructor for a Code
Code::Code() {}

//A constructor for a Code where the code vector (vect) can be set.
Code::Code(std::vector<int>vect) {
    codeVector = vect;
}

//A constructor for a Code where the code can be set using an integer (Ex. 1234)
//For the purposes the this game, the integer cannot contain more than 4 digits.
Code::Code(int code) {
    int length = 1;
    int tempCode = code;
    //Figure out the length of the integer
    while (tempCode /= 10) {
        length++;
    }
    if (length != 4) {
        std::cout << "Enter a FOUR digit integer to guess" << std::endl;
    }
    else {
        //Break down the integer into the codeVector
        while (code > 0) {
            codeVector.insert(codeVector.begin(), code%10);
            code /= 10;
        }
    }
}

//Initialize a random code into the codeVector
void Code::initializeRandomCode() {
    srand(time(NULL));
    codeVector = {randomNumberBetweenZeroAndTen(),randomNumberBetweenZeroAndTen(),randomNumberBetweenZeroAndTen(),randomNumberBetweenZeroAndTen()};
}

//Print the current code stored in codeVector
void Code::printCode() {
    for (int i = 0;i<codeVector.size(); i++) {
        std::cout << codeVector[i];
    }
    
    
}

//Compares the code object stored in this object, with another one passed as an argument
//which contains a user guess and returns the number of digits in the correct place.
int Code::checkCorrect(Code guess) {
    int correctDigits = 0;
    for (int i = 0; i<guess.codeVector.size(); i++) {
        if (codeVector[i] == guess.codeVector[i]) {
            correctDigits++;
        }
    }
    return correctDigits;
}

//Compares the code object stored in this object, with another one passed as an argument
//which contains a user guess and returns the number of correct digits in the incorrect place.
int Code::checkIncorrect(Code guess) {
    int incorrectDigits = 0;
    //Temporoarily store the digits already counted so that they don't get double counted
    std::vector<int> usedNumbers;
    for (int i = 0; i < codeVector.size(); i++) {
        if (codeVector[i] != guess.codeVector[i]) {
            for (int j = 0; j < guess.codeVector.size(); j++) {
                if (i == j) {
                    continue;
                }
                else {
                    if ((codeVector[i] == guess.codeVector[j]) && !vectorContainsInt(usedNumbers, codeVector[i])) {
                        incorrectDigits++;
                        usedNumbers.push_back(codeVector[i]);
                    }
                }
            }
        }
    }
    return incorrectDigits;
}