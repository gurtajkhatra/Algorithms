// Sample solution for project #5

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

#include <boost/graph/adjacency_list.hpp>

#include "d_except.h"
#include "d_matrix.h"


using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
    pair<int,int> cell; // maze cell (x,y) value
    Graph::vertex_descriptor pred; // predecessor node
    int weight;
    bool visited;
    bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
    int weight;
    bool visited;
    bool marked;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;



#define LargeValue 99999999
using namespace boost;
using namespace std;

class maze
{
public:
   maze(ifstream &fin);
   void print(int,int,int,int);
   bool isLegal(int i, int j);
   void mapMazeToGraph(Graph &g);
   void printPath(Graph::vertex_descriptor end,
                        stack<VertexProperties> &s,
                        Graph g);
   int numRows(){return rows;};
   int numCols(){return cols;};
   Graph::vertex_descriptor getVertexDescAt(pair<int, int> coord);
   Graph::vertex_descriptor getStartNode();
   Graph::vertex_descriptor getEndNode();
   
private:
   int rows; // number of rows in the maze
   int cols; // number of columns in the maze12 a
   
   matrix<bool> value;
   matrix<Graph::vertex_descriptor> vertex_desc;

};

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;
   
   char x;
   
   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
         fin >> x;
         if (x == 'O')
            value[i][j] = true;
         else
            value[i][j] = false;
      }
   
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}


void maze::mapMazeToGraph(Graph &g) {

    vertex_desc.resize(rows,cols);
    //Add all the verticies
    for (int i = 0; i < numCols(); i++) {
        for (int j = 0; j < numRows(); j++) {
            if (isLegal(i,j)) {
                VertexProperties v1;
                pair<int, int> newCoords(i,j);
                v1.cell = newCoords;
                v1.weight = 1;
                vertex_desc[i][j] = add_vertex(v1,g);
                
            }
        }
    }
    //Connect Edges

    for (int i = 0; i < numCols(); i++) {
        for (int j = 0; j < numRows(); j++) {
            if (isLegal(i,j)) {
                pair<Graph::edge_descriptor, bool> newEdge;
                
                //Check Left
                if (j > 0  && isLegal(i,j-1)) {
                    newEdge =  add_edge(vertex_desc[i][j], vertex_desc[i][j-1], g);
                }
                //Check right
                if (j < numRows()-1  && isLegal(i,j+1)) {
                    newEdge =add_edge(vertex_desc[i][j], vertex_desc[i][j+1], g);
                }
                //Check top
                if (i > 0  && isLegal(i-1,j)) {
                    newEdge =add_edge(vertex_desc[i][j], vertex_desc[i-1][j], g);
                }
                //Check bottom
                if (i < numCols()-1 && isLegal(i+1,j)) {
                    newEdge =add_edge(vertex_desc[i][j], vertex_desc[i+1][j], g);
                }
                Graph::edge_descriptor e = newEdge.first;
                g[e].weight = 0;
                g[e].visited = 0;
                g[e].marked = 0;
            }
        }
    }
}

Graph::vertex_descriptor maze::getVertexDescAt(pair<int, int> coord) {
    int i =coord.first;
    int j = coord.second;
    return vertex_desc[i][j];
}


Graph::vertex_descriptor maze::getStartNode() {
    return vertex_desc[0][0];
}
Graph::vertex_descriptor maze::getEndNode() {
    return vertex_desc[rows-1][cols-1];
}
// Create a graph g that represents the legal moves in the maze m.

void maze::printPath(Graph::vertex_descriptor end,
                     stack<VertexProperties> &s,
                     Graph g) {
    //Pop onto another stack to get the correct order
    stack<VertexProperties> newS;
    while (!s.empty()) {
        newS.push(s.top());
        s.pop();
    }
    cout << "Cells Visited: " << endl;
    while (!newS.empty()) {
        pair <int, int> p = newS.top().cell;
        print(g[end].cell.first, g[end].cell.second, p.first, p.second);
        //cout << p.first << ", " << p.second << endl;
        newS.pop();
        
    }
     
    
}
