//
//  Deck.cpp
//  Project2
//
//  Created by Gurtaj Khatra on 10/3/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#include "Deck.h"

//Constructs and adds all 81 cards to a deck
Deck::Deck() {
    topCard = new LinkedListNode<Card>();
    Card tempCard = Card(possibleNumbers[0], possibleShades[0], possibleSymbols[0], possibleColors[0]);
    topCard->setValue(tempCard);
    topCard->setNext(NULL);
    bool firstCard = true;
    int count = 1;
    for (int i = 0; i < possibleNumbers.size(); i++) {
        for (int j = 0; j < possibleShades.size(); j++) {
            for (int k = 0; k < possibleSymbols.size(); k++) {
                for (int l = 0; l < possibleColors.size(); l++) {
                    if (firstCard) {
                        firstCard = false;
                    }
                    else {
                        Card newCard;
                        try {
                            newCard = Card(possibleNumbers[i],possibleShades[j],possibleSymbols[k],possibleColors[l]);
                        } catch (invalid_argument &ex) {
                            cout << ex.what() << endl;
                            system("pause");
                            exit(0);
                        }
                        
                        LinkedListNode<Card> *newNode = new LinkedListNode<Card>();
                        newNode->setValue(newCard);
                        putCardOnTop(newNode);
                        count++;
                        
                    }
                }
            }
        }
    }
}

//Puts a LinkedListNode containing a card on the top of the dekc
void Deck::putCardOnTop(LinkedListNode<Card>* c) {
    c->setNext(topCard);
    topCard = c;
}


//Removes a LinkedListNode from the deck, and returns it.
LinkedListNode<Card>* Deck::removeNodeAtIndex(int index) {
    if (index >= NUMBER_OF_CARDS || index < 0) {
        throw invalid_argument("Invalid index");
    }
    LinkedListNode<Card> *prev = topCard;
    LinkedListNode<Card> *current = topCard;
    if (index == 0) {
        topCard = current->getNext();
    }
    else {
        for (int i = 0; i < index; i++) {
            prev = current;
            current = (current->getNext());
        }
        
        if (current == NULL) {
            prev->setNext(NULL);
        }
        else {
            prev->setNext(current->getNext());
        }
    }
    return current;
}

//Shuffles a deck
void Deck::shuffle() {
    int numberOfCards = NUMBER_OF_CARDS;
    cout << "Shuffling...";
    int cardToShuffle = 0;
    srand(time(NULL));
    for (int i = 0 ; i < 5000; i++) {
        cardToShuffle = (rand() % (numberOfCards));
        try {
            putCardOnTop(removeNodeAtIndex(cardToShuffle));
        } catch (invalid_argument &ex) {
            cout << ex.what() << endl;
            system("pause");
            exit(0);
        }
        
    }
    cout << endl;
}

//Puts cards from the deck into the vector v
void Deck::deal(int num, vector<Card> &v) {
    if (num < 0 || num > NUMBER_OF_CARDS) {
        throw invalid_argument("Number must be in the range of the amount of cards");
    }
    for (int i = 0; i < num; i++) {
        v.push_back(topCard->getValue());
        topCard = (topCard->getNext());
    }
}

//Puts cards from v back into the bottom of the deck
void Deck::replace(vector<Card> &v) {
    LinkedListNode<Card>* lastInDeck = topCard;
    while (lastInDeck->getNext() != NULL) {
        lastInDeck = lastInDeck->getNext();
    }
    for (int i = 0; i < v.size(); i++) {
        LinkedListNode<Card> *cardToAdd = new LinkedListNode<Card>();
        cardToAdd->setValue(v[i]);
        lastInDeck->setNext(cardToAdd);
        lastInDeck = cardToAdd;
    }
}

//Prints all the cards currenly in the deck
void Deck::printCards() {
    LinkedListNode<Card> *tempCurrentCard = topCard;
    int count = 0;
    while (tempCurrentCard != NULL) {
        cout << tempCurrentCard->getValue() << endl;
        tempCurrentCard = tempCurrentCard->getNext();
        count++;
    }
    cout << count << endl;
}