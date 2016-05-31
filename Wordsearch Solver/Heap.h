//
//  Heap.h
//  Project3B
//
//  Created by Gurtaj Khatra on 10/18/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#ifndef Heap_h
#define Heap_h
#include <stdio.h>
#include <vector>
template <class T>

class Heap {

private:
    
    
public:
    //Array containing the heap data
    std::vector<T> data;
    
    //Constructor for the heap
    Heap() {}
    
    //Deconstructor for the heap
    ~Heap() {}
    
    //Get the index of the parent
    int parent(int n) {
        if (n < data.size()) {
            return (n-1)/2;
        }
        else {
            throw std::invalid_argument("Index must be less than or equal to the data length");
        }
        
    }
    
    //Get the left child index of a node
    int left(int n) {
        if ((2*n+1) < data.size()) {
            return 2*n+1;
        }
        else {
            throw std::invalid_argument("The selected node has no left child");
        }
        
    }
    
    //Get the right child index of a node
    int right(int n) {
        if ((2*n+2) < data.size()) {
            return 2*n+2;
        }
        else {
            throw std::invalid_argument("The selected node has no right child");
        }
    }
    
    //Check if a node has a left child
    bool hasLeft(int n) {
        return (2*n+1) < data.size();
    }
    
    //Check if a node has a right child
    bool hasRight(int n) {
        return (2*n+2) < data.size();
    }
    
    //Swap two values in a vector
    void swap (int ind1, int ind2, std::vector<T>& swapIn) {
        T temp = swapIn[ind1];
        swapIn[ind1] = swapIn[ind2];
        swapIn[ind2] = temp;
    }
    
    //get an item from the heap at an index
    int getItem(int n) {
        return data[n];
    }
    
    //--------------------
    //MAX HEAP FUNCTIONS
    //--------------------
    
    //Create a max heap from a vector of values
    void initializeMaxHeap(std::vector<T> &vect) {
        buildMaxHeap(vect);
    }
    
    //Builds a max heap from the data member object
    void buildMaxHeapFromData() {
        buildMaxHeap(data);
    }
    
    //Creates a max heap from a vector
    void buildMaxHeap(std::vector<T> &vectorToMakeMaxHeap) {
        for (int i = (int)vectorToMakeMaxHeap.size()-1; i >=0; i--) {
            maxHeapify(vectorToMakeMaxHeap,i);
        }
    }
    
    //Moves an object in a heap to the correct position in the heap to satisfy the max heap property
    //Last index is the last index to check
    void maxHeapify(std::vector<T> &vectToMakeHeap, int index, int lastIndex)
    {
        int left = 2*index+1;
        int right = 2*index+2;
        int largest = index;
        if((left<=lastIndex)&& vectToMakeHeap[left]>vectToMakeHeap[largest]) {
            largest=left;
        }
        else {
            largest = index;
        }
        
        if((right<=lastIndex)&&(vectToMakeHeap[right]>vectToMakeHeap[largest])) {
            largest=right;
        }
        if(largest!=index)
        {
            swap(index, largest, vectToMakeHeap);
            maxHeapify(vectToMakeHeap, largest,lastIndex);
        }
    }

    //maxHeapify the entire tree
    void maxHeapify(std::vector<T> &vectorToMakeMaxHeap, int index) {
        maxHeapify(vectorToMakeMaxHeap, index, (int)vectorToMakeMaxHeap.size());
    }
    

    
    //--------------------
    //MIN HEAP FUNCTIONS
    //--------------------
    //Create a min heap from a vector of values
    void initializeMinHeap(std::vector<T> &vect) {
        buildMinHeap(vect);
    }
    //Create a max heap from the data member vector
    void buildMinHeapFromData() {
        buildMinHeap(data);
    }
    
    //Create a min heap from a vector of values
    void buildMinHeap(std::vector<T> &vectorToMakeMinHeap) {
        for (int i = (int)vectorToMakeMinHeap.size()-1; i >= 0; i--) {
            minHeapify(vectorToMakeMinHeap,i);
        }
    }
    
    //Moves an object in a heap to the correct position in the heap to satisfy the min heap property
    void minHeapify(std::vector<T> &vectorToMakeMinHeap, int index) {
        if (hasLeft(index) && hasRight(index)) {
            if (vectorToMakeMinHeap[left(index)] > vectorToMakeMinHeap[right(index)]) {
                if (vectorToMakeMinHeap[right(index)] < vectorToMakeMinHeap[index]) {
                    swap(index, right(index),vectorToMakeMinHeap);
                    minHeapify(vectorToMakeMinHeap,right(index));
                }
            }
            else {
                if (vectorToMakeMinHeap[left(index)] < vectorToMakeMinHeap[index]) {
                    swap(index, left(index));
                    minHeapify(vectorToMakeMinHeap,left(index),vectorToMakeMinHeap);
                }
            }
        }
        else if(hasLeft(index)) {
            if (vectorToMakeMinHeap[left(index)] < vectorToMakeMinHeap[index]) {
                swap(index, left(index));
                minHeapify(vectorToMakeMinHeap,left(index),vectorToMakeMinHeap);
            }
            
        }
        
    }
    
    
    //Heapsorts the data member vector.
    void heapsort() {
        int end = (int)data.size()-1;
        try {
            buildMaxHeapFromData();
        } catch (std::invalid_argument ex) {
            std::cout << ex.what() << std::endl;
        }
        
        for (int i = end; i >=1; i--) {
            swap(0, i, data);
            //end = end-1;
            maxHeapify(data, 0, i-1);
        }
        /*while (end >= 0) {
            swap(0, end, data);
            maxHeapify(data, 0, end);
            end = end-1;
            
        }*/
    }

};


#endif /* Heap_h */
