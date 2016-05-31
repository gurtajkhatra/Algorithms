//
//  Hashtable.h
//  Project3B
//
//  Created by Gurtaj Khatra on 10/19/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#ifndef Hashtable_h
#define Hashtable_h
#include <stdio.h>
#include <vector>
template <class T>

class Hashtable {
public:
    //The actual hashtable
    std::vector<std::vector<T>> hashtable;
    //Size of the hashtable
    int size;
    
    //Constructor for the hashtable
    Hashtable(int tableSize) {
        size = tableSize;
        hashtable.resize(tableSize);
    }
    
    //Hash an item
    int hash(T item) {
        std::hash<T> hasher;
        return hasher(item) % size;
    }
    
    //Add item to hash table
    void addItem(T item) {
        int index = hash(item);
        hashtable[index].push_back(item);
    }
    
    //Delete an item from the hash table
    void deleteItem(T item) {
        int indexToSeach = hash(item);
        for (int i = 0; i < hashtable[indexToSeach].size(); i++) {
            if (hashtable[indexToSeach][i] == item) {
                hashtable.erase(hashtable.begin()+i);
            }
        }
    }
    
    //Check if an item is in the hashtable
    bool inList(T item) {
        int indexToSeach = hash(item);
        for (int i = 0; i < hashtable[indexToSeach].size(); i++) {
            if (hashtable[indexToSeach][i] == item){
                return true;
            }
        }
        return false;
    }
    
};


#endif /* Hashtable_h */
