//
//  Grid.cpp
//  Project3a
//
//  Created by Gurtaj Khatra on 10/11/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#include "Grid.h"
#include <iostream>

//Loads a Grid of a file specified in the gridPath.
void Grid::loadGrid() {
    int lineNum = -1;
    string line;
    ifstream gridData(gridPath);
    while ( getline (gridData,line) )
    {
        if (lineNum == -1) {
            string gridWidth = "";
            string gridHeight = "";
            for (char ascii:line) {
                if (ascii == ' ') {
                    break;
                }
                gridWidth += ascii;
            }
            for (char ascii:line) {
                if (ascii == ' ') {
                    break;
                }
                gridHeight += ascii;
            }
            int height = stoi(gridHeight);
            int width = stoi(gridWidth);
            grid = matrix<string>();
            grid.resize(height, width);
            this->height = height;
            this->width = width;
            lineNum++;
        }
        else {
            int column = 0;
            for (char ascii:line){
                if (ascii == ' ') {
                    continue;
                }
                else {
                    grid[lineNum][column] = ascii;
                    column++;
                }
            }
            lineNum++;
        }
        
    }
}

//Prints a grid to the console
void Grid::printGrid() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}