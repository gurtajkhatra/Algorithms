//
//  main.cpp
//  Project2
//
//  Created by Gurtaj Khatra on 10/3/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#include <iostream>
#include "Deck.h"
#include "Card.h"
//#include <time.h>

//Initailzes a deck, shuffles it, deals 12 cards and then finds all the sets in it
void playSet() {
    Deck d;
    d.shuffle();
    vector<Card> cards;
    try {
        d.deal(12, cards);
    } catch (invalid_argument &ex) {
        cout << ex.what() << endl;
        system("pause");
        exit(0);
    }
    bool foundSet = false;
    for (int i = 0; i < 12; i++) {
        for (int j = i+1; j < 12; j++) {
            for (int k = j + 1; k < 12; k++) {
                if (cards[i].makesSetWithCards(cards[j], cards[k])) {
                    foundSet = true;
                    cout << "Found a set: " << endl;
                    cout << cards[i] << endl;
                    cout << cards[j] << endl;
                    cout << cards[k] << endl;
                    cout << "--------------------------" << endl;
                }
            }
        }
    }
    if (!foundSet) {
        cout << "No Set Found!" << endl;
    }
    d.replace(cards);
}

//Helper function to check if a card c makes a set with any pair of cards in a vector of cards
bool makesSetWithElementsInVector(Card c, vector<Card> cards) {
    for (int i = 0; i < cards.size(); i++) {
        for (int j = 0; j < cards.size(); j++) {
            if (i != j) {
                if (c.makesSetWithCards(cards[i], cards[j])) {
                    return true;
                }
            }
        }
    }
    return false;
}

//Finds the largest set of cards that form a nonset
void findLargestNonSet() {
    Deck d;
    d.shuffle();
    vector<Card> cards;
    d.deal(81, cards);
    vector<Card> nonSet;
    vector<Card> maxNonSet;
    //The max nonset set of cards while only looking at two of the properties of the
    //cards is going to be a subset of the max size set of cards that make a non set while looking at
    //all the properties of the cards. We use this fact to narrow down the search and speed it up by having
    //to search through fewer cards to find the first two.
    //we are going to find the max set of cards that make a non set where the first two cards both have
    //the same shade and color, and the only property that changes is going to be the number and color.
    
    //Use this first for loop to pick the first card
    for (int i = 0; i < cards.size(); i++) {
            if (cards[i].getColor() == cards[0].getColor() && cards[i].getShading() == cards[0].getShading()) {
                //Use this for loop to pick the second card
                for (int j = 0; j < cards.size(); j++) {
                    if (cards[j].getColor() == cards[0].getColor() && cards[j].getShading() == cards[0].getShading()) {
                        nonSet = {cards[i], cards[j]};
                        //Iterate through the rest of the cards
                        for (int k = 0; k < cards.size(); k++) {
                                if (!makesSetWithElementsInVector(cards[k], nonSet)) {
                                    nonSet.push_back(cards[k]);
                                }
                            }
                            if (nonSet.size() > maxNonSet.size()) {
                                maxNonSet = nonSet;
                                nonSet = {};
                            }
                        }
                    }
                }
            }
    cout << "Max amount of cards without a set is: " << (int)maxNonSet.size() << endl;
    cout << "The contents of the nonset are: " << endl;
    for (int i = 0; i < maxNonSet.size(); i++) {
        cout << maxNonSet[i] << endl;
    }
}

int main(int argc, const char * argv[]) {
    playSet();
    cout << "--------------------------" << endl;
    findLargestNonSet();
    system("pause");
    return 0;
}
