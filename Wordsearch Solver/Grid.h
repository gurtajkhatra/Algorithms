//
//  Grid.hpp
//  Project3a
//
//  Created by Gurtaj Khatra on 10/11/15.
//  Copyright © 2015 Gurtaj Khatra. All rights reserved.
//

#ifndef Grid_h
#define Grid_h

#include <stdio.h>
#include "matrix.h"
#include <string>
#include <fstream>
class Grid {

private:
    
    
public:
    //A grid containing the letters
    matrix<string> grid;
    //File location of the grid .txt file
    string gridPath;
    //Height of the grid
    int height;
    //Width of the grid
    int width;
    
    
    void loadGrid();
    void printGrid();
    
};

#endif /* Grid_h */
