// Declarations and functions for the Sudoku project

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
//  (usually 3).  The board has
//  SquareSize^2 rows and SquareSize^2
//  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

class board
// Stores the entire Sudoku board
{
public:
    board(int);
    void clear();
    void initialize(ifstream &fin);
    void print();
    void printConflicts();
    bool isBlank(int, int);
    ValueType getCell(int, int);
    void  setCell(int i,int j, ValueType val);
    void clearCell(int i, int j);
    bool doesCauseConflict(int row, int column, int value);
    void updateConflicts();
    bool isSolved();
    bool solve();
    bool solve(int row, int column);
    void printNumberOfRecursiveCalls();
    vector<int> findMaxNumberConflictsIndex();
    
    //Conflicts is a matrix of the same size as value, but at each index is a vector of booleans.
    //If a boolean at a vector index is True, then the number of the index causes a conflict at that position. This design is less space efficient than just storing possible nubmers that would cause conflict, but it is more time efficient, since lookup can be done in O(1) time.
    matrix<vector<bool>>conflicts;
    
    //Stores the number of recursive calls
    int recursiveCalls = 0;
    
private:
    
    // The following matrices go from 1 to BoardSize in each
    // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
    
    matrix<ValueType> value;
   
    //Stores all of the digits that are currently originally placed on the board
    matrix<ValueType>originalDigits;
    
    //Stores all of the digits that are placed on the the board
    matrix<ValueType>placedDigits;
    
    
};

board::board(int sqSize)
: value(BoardSize+1,BoardSize+1)
// Board constructor
{
}

void board::clear()
// Clear the entire board.
{
    for (int i = 1; i <= BoardSize; i++) {
        for (int j = 1; j <= BoardSize; j++) {
            if (originalDigits[i][j] != Blank) {
                value[i][j] = Blank;
            }
        }
    }
    recursiveCalls = 0;
}

void  board::setCell(int i,int j, ValueType val) {
// set cell i,j to val and update conflicts
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize) {
        value[i][j] = val;
        placedDigits[i][j] = val;
        updateConflicts();
    }
    else
        throw rangeError("bad value in getCell");
    
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file, and initalize the conflicts
{
    originalDigits = {};
    placedDigits = {};
    conflicts = {};
    originalDigits.resize(BoardSize+1, BoardSize+1);
    placedDigits.resize(BoardSize+1, BoardSize+1);
    //Initialize conflicts board
    conflicts.resize(BoardSize+1, BoardSize+1);
    
    for (int i = 1; i <= BoardSize; i++) {
        for (int j = 1; j <= BoardSize; j++) {
            conflicts[i][j] = {false,false,false,false,false,false,false,false,false,false};
        }
    }
    
    char ch;
    
    clear();
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
        {
            fin >> ch;
            
            // If the read char is not Blank
            if (ch != '.')
            {
                
                setCell(i,j,ch-'0');// Convert char to int
                
            }
        }
   
    
    for (int i = 1; i <= BoardSize; i++) {
        for (int j = 1; j <= BoardSize; j++) {
            if (value[i][j] != Blank) {
                originalDigits[i][j] = value[i][j];
            }
            else {
                originalDigits[i][j] = Blank;
            }
            placedDigits[i][j] = Blank;
        }
    }
    updateConflicts();
}



int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
    // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
    // coordinates of the square that i,j is in.
    
    return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}


//Updates the conflicts in the board
void board::updateConflicts() {
    //Reset all the conflicts
    for (int j = 1; j <= BoardSize; j++) {
        for (int k = 1; k <= BoardSize; k++) {
            for (int i = 1; i <= BoardSize; i++) {
                conflicts[j][k][i] = false;
            }
        }
    }
    //Set all the conflicts now
    for (int j = 1; j <= BoardSize; j++) {
        for (int k = 1; k <= BoardSize; k++) {
            int row = j;
            int col = k;
            ValueType val = value[j][k];
            if (val > Blank) {
                
                
                //Update the row conflicts
                for (int i = 1; i <= BoardSize; i++) {
                    conflicts[i][col][val] = true;
                }
                //Update the column conflicts
                for (int i = 1; i <= BoardSize; i++) {
                    conflicts[row][i][val] = true;
                }
                //Update the square conflicts
                int startRowIndex = row-(row-1)%3;
                int startColumnIndex = col - (col-1)%3;
                for (int i = startRowIndex; i < startRowIndex + 3; i++) {
                    for (int m = startColumnIndex; m < startColumnIndex + 3; m++) {
                        conflicts[i][m][val] = true;
                    }
                }
            }
        }
    }
    
}

//Checks if adding a number to a specific row/column will cause a conflict
bool board::doesCauseConflict(int row, int column, int value) {
    return conflicts[row][column][value];
}

//Clears a cell in the board and updates the conflicts
void board::clearCell(int i, int j) {
    setCell(i, j, Blank);
    placedDigits[i][j] = Blank;
    
}

//Checks if the sudoku is solved
bool board::isSolved() {
    for (int i = 1; i <= BoardSize ; i++) {
        for (int j = 1; j <= BoardSize; j++) {
            if (value[i][j] == Blank) {
                return false;
            }
        }
    }
    return true;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
    for (int i = 0; i < v.size(); i++)
        ostr << v[i] << " ";
    ostr << endl;
    return ostr;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
        return value[i][j];
    else
        throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
        throw rangeError("bad value in setCell");
    return getCell(i, j) == -1;
}

void board::print()
// Prints the current board.
{
    for (int i = 1; i <= BoardSize; i++)
    {
        if ((i-1) % SquareSize == 0)
        {
            cout << " -";
            for (int j = 1; j <= BoardSize; j++)
                cout << "---";
            cout << "-";
            cout << endl;
        }
        for (int j = 1; j <= BoardSize; j++)
        {
            if ((j-1) % SquareSize == 0)
                cout << "|";
            if (!isBlank(i,j))
                cout << " " << getCell(i,j) << " ";
            else
                cout << "   ";
        }
        cout << "|";
        cout << endl;
    }
    
    cout << " -";
    for (int j = 1; j <= BoardSize; j++)
        cout << "---";
    cout << "-";
    cout << endl;
    cout << endl;
    
}

void board::printNumberOfRecursiveCalls() {
    cout << recursiveCalls << endl;
}

//Prints all the conflicts
void board::printConflicts() {
    cout << "------------------------Conflicts--------------------------" << endl;
    cout << "                                 1  2  3  4  5  6  7  8  9" << endl;
    cout << "                                ---------------------------" << endl;
    for (int i = 1; i <= BoardSize; i++) {
        for (int j = 1; j <= BoardSize; j++) {
            cout << "Conflicts for Row: " << i << " Column: " << j << ": ";
            cout << "[";
            for (int k = 1; k < BoardSize; k++) {
                cout << conflicts[i][j][k] << ", ";
            }
            cout << conflicts[i][j][BoardSize] << "]" << endl;
        }
    }
}

vector<int> board::findMaxNumberConflictsIndex() {
    int startRow = 1;
    int startCol = 1;
    bool found = false;
    for (int i = 1; i <= BoardSize; i++) {
        for (int j = 1; j <= BoardSize; j++) {
            if (isBlank(i, j)) {
                startRow = i;
                startCol = j;
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    
    int currMaxConflicts = 0;
    
    for (int i = 1; i <= BoardSize; i++) {
        for (int j = 1; j <=BoardSize; j++) {
            int tempMax = 0;
            for (int k = 1; k <= BoardSize; k++) {
                if (conflicts[i][j][k] == true) {
                    tempMax++;
                }
            }
            if (currMaxConflicts < tempMax && tempMax != BoardSize && placedDigits[i][j] == Blank && originalDigits[i][j] == Blank) {
                currMaxConflicts = tempMax;
                startRow = i;
                startCol = j;
            }
        }
    }
    
    //print();
    return {startRow, startCol};
}



bool board::solve() {
    recursiveCalls = recursiveCalls +1;
    if (isSolved()) {
        return true;
    }
    
    else {
        vector<int> indexToAddTo = findMaxNumberConflictsIndex();
        int newRow = indexToAddTo[0];
        int newCol = indexToAddTo[1];
        for (int i = 1; i <= BoardSize; i++) {
            if (conflicts[newRow][newCol][i] == false) {
                setCell(newRow, newCol, i);
                print();
                if (solve()) {
                    
                    return true;
                }
            }
        }
        clearCell(newRow, newCol);
    }
    return false;
}




int main()
{
    ifstream fin;
    
    // Read the sample grid from the file.
    string fileName = "/Users/Gurtaj/Dropbox/College Work/Middler/Algorithms/Project 4B/Project 4B/sudoku.txt";
    
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    
    try
    {
        board b1(SquareSize);
        vector<int> vectOfNumOfCalls = {};
        while (fin && fin.peek() != 'Z')
        {
            b1.initialize(fin);
            b1.print();
            vector<int> startIndex = b1.findMaxNumberConflictsIndex();
            b1.solve();
            b1.print();
            b1.printNumberOfRecursiveCalls();
            vectOfNumOfCalls.push_back(b1.recursiveCalls);
            b1.clear();
            //b1.printConflicts();
        }
        
        cout << "Number of Recursive Callers per Sudoku: ";
        for (int i = 0; i < vectOfNumOfCalls.size(); i++) {
            cout << vectOfNumOfCalls[i] << ", ";
        }
        
    }
    catch  (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }

    
    //vector<int> startIndex = b1.findMaxNumberConflictsIndex();
    
    
    //b1.solve(startIndex[0], startIndex[1]);
    //b1.print();
    //b1.printNumberOfRecursiveCalls();
    
    
}
