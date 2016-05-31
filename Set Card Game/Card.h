//
//  Card.hpp
//  Project2
//
//  Created by Gurtaj Khatra on 10/3/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#ifndef Card_h
#define Card_h

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Card {
private:
    //Number on a card
    int number;
    //shading on a card
    string shading;
    //symbol on a card
    string symbol;
    //color of a card
    string color;
    
public:
    Card();
    ~Card();
    int getNumber();
    string getShading();
    string getSymbol();
    string getColor();
    Card(int number, string shading, string symbol, string color);
    bool makesSetWithCards(Card c1, Card c2);
    friend ostream& operator<<(ostream& out,const Card& c);
};

#endif /* Card_h */
