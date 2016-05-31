
#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include "maze.h"

using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;



// typedef property<edge_weight_t, int> EdgeProperty;

#define LargeValue 99999999

void clearVisited(Graph &g) {
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
        g[*vItr].visited = false;
    }
}
// Mark all nodes in g as not visited.

void setNodeWeights(Graph &g, int w) {
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
        g[*vItr].weight = w;
    }
}
// Set all node weights to w.

void clearMarked(Graph &g) {
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
        g[*vItr].marked = false;
    }
}

ostream &operator<<(ostream &ostr, const Graph &g) {
    cout << "----------NODES--------------" << endl;
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
        cout << "Cell: (" << g[*vItr].cell.first << ", " << g[*vItr].cell.second << ") " << "Visited: " << g[*vItr].visited << " Marked: " << g[*vItr].marked << " Weight: " << g[*vItr].weight << endl;
    }
    cout << "----------EDGES--------------" << endl;
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
    
    for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr) {
        cout << "Visited: " << g[*eItr].visited << " Marked: " << g[*eItr].marked << " Weight: " << g[*eItr].weight << endl;
    }
    return ostr;
}


void findPathDFSRecursive(Graph &g, maze &m ,Graph::vertex_descriptor current, Graph::vertex_descriptor &end, stack<VertexProperties> currPath) {
    if (end == current) {
        m.printPath(end, currPath, g);
        return;
    }
    else {
        //Mark the current node as visited
        g[current].visited = true;
        //Get all nodes adjacent to the current pair
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(current, g);
        for (Graph::adjacency_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
            pair<int,int> currentLocation = g[*vItr].cell;
            if (!g[*vItr].visited) {
                g[*vItr].visited = true;
                Graph::vertex_descriptor newCurr = m.getVertexDescAt(g[*vItr].cell);
                currPath.push(g[*vItr]);
                findPathDFSRecursive(g, m, newCurr, end, currPath);
                currPath.pop();
                g[*vItr].visited = false;
            }
        }
    }
}


void findPathDFSStack (Graph &g, maze &m) {
    Graph::vertex_descriptor start =m.getStartNode();
    Graph::vertex_descriptor end =m.getEndNode();
    map<pair<int, int>, pair<int, int>> path;
    stack<VertexProperties> s;
    //g[start].visited = true;
    s.push(g[start]);
    int count = 0;
    bool found = false;
    while (!s.empty()) {
        VertexProperties v = s.top();
        s.pop();
        if (!v.visited) {
            g[m.getVertexDescAt(v.cell)].visited = true;
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(m.getVertexDescAt(v.cell), g);
            for (Graph::adjacency_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
                if (!g[*vItr].visited) {
                    s.push(g[*vItr]);
                    path[g[*vItr].cell] = v.cell;
                    if (g[*vItr].cell == g[end].cell) {
                        found = true;
                        while (!s.empty()) {
                            s.pop();
                        }
                    }
                }
            }
        }
    }
    
    if (found) {
        //Unload the map to a stack to print it
        pair<int, int> current = g[end].cell;
        pair<int, int> startPair = g[start].cell;
        stack <pair<int, int>> reversePath;
        do {
            reversePath.push(current);
            current = path[current];
        } while (current != startPair);
        reversePath.push(g[start].cell);
        cout << "Cells Visited: " << endl;
        int count = 0;
        while (!reversePath.empty()) {
            count++;
            m.print(g[end].cell.first, g[end].cell.second, reversePath.top().first, reversePath.top().second);
            //cout << reversePath.top().first << ", " << reversePath.top().second << endl;
            reversePath.pop();
        }
        //cout << "Length: " << count << endl;
    }
    else {
        cout << "No Path Found" << endl;
    }
}

void findShortestPathDFS (Graph &g, maze m) {
    Graph::vertex_descriptor start =m.getStartNode();
    Graph::vertex_descriptor end =m.getEndNode();
    
    stack<VertexProperties> s;
    s.push(g[start]);
    vector<vector<VertexProperties>> paths;
    
    while (!s.empty()) {
        VertexProperties v = s.top();
        s.pop();
        if (!v.visited) {
            g[m.getVertexDescAt(v.cell)].visited = true;
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(m.getVertexDescAt(v.cell), g);
            for (Graph::adjacency_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
                if (!g[*vItr].visited) {
                    g[*vItr].pred = m.getVertexDescAt(v.cell);
                    s.push(g[*vItr]);
                    
                    
                    if (g[*vItr].cell == g[end].cell) {
                        vector<VertexProperties> v;
                        VertexProperties curr = g[end];
                        while (curr.cell != g[start].cell) {
                            v.push_back(curr);
                            curr = g[curr.pred];
                        }
                        paths.push_back(v);
                        
                    }
                }
            }
        }
    }
    int minSize = m.numRows()*m.numCols();
    int minIndex = 0;
    if (paths.size() == 0) {
        cout << "No Solution Found" << endl;
    }
    else {
        for (int i = 0; i < paths.size(); i++) {
            if (minSize > paths[i].size()) {
                minIndex = i;
            }
        }
        
        for (int i = paths[minIndex].size()-1; i >=0; i--) {
            m.print(g[end].cell.first, g[end].cell.second, paths[minIndex][i].cell.first, paths[minIndex][i].cell.second);
            //cout << paths[minIndex][i].cell.first << ", " << paths[minIndex][i].cell.second << endl;
        }
        cout << "Length: " << paths[minIndex].size() << endl;
    }
    
}

void findShortestPathBFS (Graph &g, maze &m) {
    queue<VertexProperties> q;
    Graph::vertex_descriptor start =m.getStartNode();
    Graph::vertex_descriptor end =m.getEndNode();
    q.push(g[start]);
    g[start].visited = true;
    VertexProperties endVert;
    bool found = false;
    while (!found) {
        VertexProperties v = q.front();
        q.pop();
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(m.getVertexDescAt(v.cell), g);
        for (Graph::adjacency_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
            if (!g[*vItr].visited) {
                g[*vItr].visited = true;
                g[*vItr].pred = m.getVertexDescAt(v.cell);
                q.push(g[*vItr]);
                if (g[*vItr].cell == g[end].cell) {
                    found = true;
                    endVert = g[*vItr];
                }
            }
        }
        
    }
    if (found) {
        //Follow the path of prev's
        stack<pair<int, int>> revPath;
        Graph::vertex_descriptor current = m.getVertexDescAt(endVert.cell);
        while (current != start) {
            revPath.push(g[current].cell);
            current = g[current].pred;
        }
        
        while (!revPath.empty()) {
            m.print(g[end].cell.first, g[end].cell.second, revPath.top().first, revPath.top().second);
            //cout << revPath.top().first << ", " << revPath.top().second << endl;
            revPath.pop();
        }
    }
    else {
        cout << "No Path Found" << endl;
    }
}


// Output operator for the Graph class. Prints out all nodes and their
// properties, and all edges and their properties.
   
int main()
{
//   try
//   {
    ifstream fin;

    // Read the maze from the file.
    
    
    
    //REPLACE THIS FILE PATH
    //---------------------------------------------------------------------------------------------------
    string fileName = "/Users/Gurtaj/Dropbox/College Work/Middler/Algorithms/HW5a/HW5a/maze-files/maze0.txt";
    //---------------------------------------------------------------------------------------------------

    
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << "Please make sure to replace the file path on line 260." << endl;
        exit(1);
    }

    maze m(fin);
    fin.close();
    
    Graph g;
    m.mapMazeToGraph(g);
    clearVisited(g);
    //cout << g;
    
    stack <VertexProperties> path;
    Graph::vertex_descriptor start =m.getStartNode();
    Graph::vertex_descriptor end =m.getEndNode();
    
    
    
    cout << "___________USING DFS STACK___________" << endl << endl;
    findPathDFSStack(g, m);
    clearVisited(g);
    cout << endl << endl;
//
    cout << "___________SHORTEST USING BFS________________" << endl << endl;
    findShortestPathBFS(g, m);
    clearVisited(g);
    cout << endl << endl;
    
    cout << "___________SHORTEST USING DFS________________" << endl << endl;
    findShortestPathDFS(g, m);
    clearVisited(g);
    cout << endl << endl;
    
    cout << "___________USING DFS RECURSIVE___________" << endl << endl;
    findPathDFSRecursive(g, m, start, end, path);
    clearVisited(g);
    cout << endl << endl;
    
//}
}
