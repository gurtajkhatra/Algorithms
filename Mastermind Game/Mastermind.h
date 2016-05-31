//
//  Mastermind.h
//  Project1a
//
//  Created by Gurtaj Khatra on 9/20/15.
//  Header file for a mastermind object

#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <stdio.h>
#include "code.h"
#include "response.h"


class Mastermind {
private:
    //The code that needs to be guessed
    Code answer;
    
public:
    void printCode();
    Code humanGuess();
    Response getResponse(Code guess, Code secretCode);
    bool isSolved(Response resp);
    void playGame();
    
};

#endif // CODE_H
