//
//  response.h
//  Project1a
//
//  Created by Gurtaj Khatra on 9/20/15.
//  Header file for a response object

#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>

class Response {
private:
    //The number of correct digits in the correct place.
    int numberCorrect;
    //The number of correct digits in the incorrect place
    int numberIncorrect;
public:
    Response(){};
    int getNumberCorrect();
    int getNumberIncorrect();
    void setNumberCorrect(int numberCorrect);
    void setNumberIncorrect(int numberIncorrect);
    bool sameResponse(Response resp);
    void printResponse();
};


#endif // RESPONSE_H