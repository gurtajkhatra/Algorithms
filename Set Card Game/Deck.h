//
//  Deck.hpp
//  Project2
//
//  Created by Gurtaj Khatra on 10/3/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#ifndef Deck_h
#define Deck_h

#define NUMBER_OF_CARDS 81

#include <stdio.h>
#include "LinkedListNode.h"
#include "Card.h"

class Deck {
private:
    //Top card of the deck (head of the linked list)
    LinkedListNode<Card> *topCard;
    //Possible numbers for contained cards
    const vector<int> possibleNumbers = {1,2,3};
    //Possible shades for contained cards
    const vector<string> possibleShades = {"solid", "striped", "open"};
    //Possible symbols for contained cards
    const vector<string> possibleSymbols = {"diamond", "squiggle", "oval"};
    //Possible colors for contained cards
    const vector<string> possibleColors = {"red", "green", "purple"};
public:
    Deck();
    void putCardOnTop(LinkedListNode<Card>* c);
    LinkedListNode<Card>* removeNodeAtIndex(int index);
    void printCards();
    void shuffle();
    void deal(int num, vector<Card> &v);
    void replace(vector<Card> &v);
};

#endif /* Deck_h */
