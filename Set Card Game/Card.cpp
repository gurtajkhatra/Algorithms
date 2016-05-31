//
//  Card.cpp
//  Project2
//
//  Created by Gurtaj Khatra on 10/3/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#include "Card.h"
//Constructor for a Card
Card::Card() {

}

//Deconstructor for a card
Card::~Card() {
}


//Another constructor for a card
Card::Card(int num, string sha, string symb, string col) {
    if (num > 3 || num < 1) {
            throw invalid_argument("number must be in the range of [1,3]");
    }
    if (!(sha == "solid" || sha == "striped" || sha == "open")) {
        throw invalid_argument("shade must be either solid, striped  or open");
    }
    if (!(symb == "diamond" || symb == "squiggle" || symb == "oval")) {
        throw invalid_argument("symbol must be either diamond, squiggle, or oval");
    }
    if (!(col == "green" || col == "red" || col == "purple")) {
        throw invalid_argument("color must be either green, red, purple");
    }
    number = num;
    shading = sha;
    symbol = symb;
    color = col;
}

//getter for number
int Card::getNumber() {
    return number;
}

//getter for shading
string Card::getShading() {
    return shading;
}

//getter for symbol
string Card::getSymbol() {
    return symbol;
}

//getter for color
string Card::getColor() {
    return color;
}


//checks if two cards have the same number
//Returns true if it does, false if it doesn't
bool sameNumber(Card c1, Card c2) {
    return c1.getNumber() == c2.getNumber();
}


//checks if two cards have the same shading
//Returns true if it does, false if it doesn't
bool sameShading(Card c1, Card c2) {
    return c1.getShading() == c2.getShading();
}


//checks if two cards have the same symbol
//Returns true if it does, false if it doesn't
bool sameSymbol(Card c1, Card c2) {
    return c1.getSymbol() == c2.getSymbol();
}

//checks if two cards have the same color,
//Returns true if it does, false if it doesn't
bool sameColor(Card c1, Card c2) {
    return c1.getColor() == c2.getColor();
}

//Checks if this card makes a set with two other cards
//Returns true if it does, false if it doesn't
bool Card::makesSetWithCards(Card c1, Card c2) {
    bool out = ((sameNumber(*this, c1) && sameNumber(*this, c2) && sameNumber(c1, c2)) || (!sameNumber(*this, c1) && !sameNumber(*this, c2) && !sameNumber(c1, c2))) &&
    ((sameShading(*this, c1) && sameShading(*this, c2) && sameShading(c1, c2)) || (!sameShading(*this, c1) && !sameShading(*this, c2) &&  !sameShading(c1, c2))) &&
    ((sameSymbol(*this, c1) && sameSymbol(*this, c2) && sameSymbol(c1, c2)) || (!sameSymbol(*this, c1) && !sameSymbol(*this, c2) && !sameSymbol(c1, c2))) &&
    ((sameColor(*this, c1) && sameColor(*this, c2) && sameColor(c1, c2)) || (!sameColor(*this, c1) && !sameColor(*this, c2) && !sameColor(c1, c2)));
    return out;
}

//Operator overloader for << to print out the contents of a card
ostream& operator<<(ostream& out,const Card& c) {
    out << "  " << c.number << "  " << c.shading << "  " << c.symbol << "  " << c.color;
    return out;
}