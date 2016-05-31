//
//  LinkedListNode.h
//  Project2
//
//  Created by Gurtaj Khatra on 10/3/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#ifndef LinkedListNode_h
#define LinkedListNode_h

#include <stdio.h>

template <class T>
class LinkedListNode {
    //Next node in the linked list
    LinkedListNode<T> *next;
    //Contents of the current node
    T current;
public:
    //Constructor
    LinkedListNode(){};
    //Deconstructor
    ~LinkedListNode(){
        delete next;
    }
    //Constructor with ability to add contents
    LinkedListNode(T curr){
         current = curr;
    }
    //Constructor with ability to add contents and a pointer to the
    //next element in the list
    LinkedListNode(T curr, LinkedListNode<T> *next){
        current = curr;
        this->next = next;
    }
    //Get the contents of this node
    T getValue() {
        return current;
    }
    //Set the contents of this node
    void setValue(T val) {
        current = val;
    }
    //Set the pointer to the next element in the linked list
    void setNext(LinkedListNode<T>* val) {
        next = val;
    }
    //Get the pointer to the next element in the linked list
    LinkedListNode<T>* getNext() {
        return next;
    }
};

#endif /* LinkedListNode_h */
