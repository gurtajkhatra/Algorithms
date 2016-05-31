//
//  response.cpp
//  Project1a
//  Created by Gurtaj Khatra on 9/20/15.
//  Implementation of the response class

#include "response.h"
#include <iostream>

//Getter for the numberCorrect data member
int Response::getNumberCorrect() {
    return numberCorrect;
}

//Getter for the numberIncorrect data member
int Response::getNumberIncorrect() {
    return numberIncorrect;
}

//Set the numberCorrect data memeber
void Response::setNumberCorrect(int numCorrect) {
    numberCorrect = numCorrect;
}

//Set the numberIncorrect data member
void Response::setNumberIncorrect(int numIncorrect) {
    numberIncorrect = numIncorrect;
}

//Compares this response with another one that it passed to it.
//Returns true if the responses are the same, and false if they are different.
//This function assumes that all it takes for two responses to be equal is for the
//numberCorrect and numberIncorrect data members of each response to be equal.
bool Response::sameResponse(Response resp) {
    return ((numberCorrect == resp.numberCorrect) && (numberIncorrect == resp.numberIncorrect));
}

//Prints a response in the following format:
//"<numberCorrect>, <numberIncorrect>"
void Response::printResponse() {
    std::cout << numberCorrect << "," << numberIncorrect << std::endl;
    
}
