//
//  Mastermind.cpp
//  Project1a
//
//  Created by Gurtaj Khatra on 9/20/15.
//  Implementation for a mastermind object

#include "Mastermind.h"
#include <iostream>

//Print the code that needs to be guessed
void Mastermind::printCode() {
    answer.printCode();
}

//Prompts the user for a guess, and returns a code object
//containing that guess
Code Mastermind::humanGuess() {
    std::cout << "Enter a four digit code: ";
    int code;
    std::cin >> code;
    return Code(code);
}

//Generates a Response object from two Code objects (a guess and the secret code)
//and returns it.
Response Mastermind::getResponse(Code guess, Code secretCode) {
    Response resp;
    resp.setNumberCorrect(secretCode.checkCorrect(guess));
    resp.setNumberIncorrect(secretCode.checkIncorrect(guess));
    return resp;
}

//Checks to see if the code has been cracked yet.
//Returns true if it has, false if it has not.
bool Mastermind::isSolved(Response resp) {
    Response solved;
    solved.setNumberCorrect(4);
    solved.setNumberIncorrect(0);
    //Checks if the current response object is equal to the response when the
    //puzzle is solved.
    return (resp.sameResponse(solved));
}

//Main function for initializing and playing the game.
//Generates a random code. and continuously prompts the user for
//guesses until one side wins.
void Mastermind::playGame() {
    Code randCode;
    randCode.initializeRandomCode();
    std::cout << "The Random Code is: ";
    randCode.printCode();
    std::cout << std::endl;
    int guesses = 10;
    while (guesses > 0) {
        Code guess = humanGuess();
        Response resp = getResponse(guess, randCode);
        resp.printResponse();
        if (isSolved(resp)) {
            break;
        }
        guesses--;
    }
    if (guesses != 0) {
        std::cout << "The Code Breaker Wins";
    }
    else {
        std::cout << "The Code Maker Wins";
    }
}