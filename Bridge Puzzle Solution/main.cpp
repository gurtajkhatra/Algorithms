
#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <stack>
#include <boost/graph/adjacency_list.hpp>
#include <limits.h>
#include <fstream>
#include "d_except.h"
#include <queue>

#define LargeValue 999999999
#define SmallValue -999999999

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

int graphSize = 0;



void initializeGraph(Graph &g,
                     Graph::vertex_descriptor &start,
                     Graph::vertex_descriptor &end, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal
// to the start and end nodes.
{
    EdgeProperties e;
    
    int n, i, j;
    int startId, endId;
    fin >> n;
    //fin >> startId >> endId;
    startId = 0;
    endId = n-1;
    Graph::vertex_descriptor v;
    
    // Add nodes.
    for (int i = 0; i < n; i++)
    {
        v = add_vertex(g);
        if (i == startId)
            start = v;
        if (i == endId)
            end = v;
    }
    
    while (fin.peek() != '.')
    {
        fin >> i >> j >> e.weight;
        add_edge(i,j,e,g);
    }
}



bool isConnected(Graph &g) {
    stack<Graph::vertex_descriptor> s;
    int numVerticies = num_vertices(g);
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    
    s.push(*(vItrRange.first));
    int nodeCount = 0;
    while (!s.empty()) {
        Graph::vertex_descriptor v = s.top();
        
        s.pop();
        if (!(g[v].visited)) {
            g[v].visited = true;
            nodeCount = nodeCount + 1;
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange2 = adjacent_vertices(v, g);
            for (Graph::adjacency_iterator vItr= vItrRange2.first; vItr != vItrRange2.second; ++vItr) {
                if (!g[*vItr].visited) {
                    s.push(*vItr);
                    
                }
            }
        }
    }
    
    if (nodeCount == numVerticies) {
        return true;
    }
    else {
        return false;
    }
}

void resetVisited(Graph &g) {
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    
    // Loop over all nodes in the graph
    for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
        g[*vItr].visited = false;

    }
    
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
    
    // Loop over all edges in the graph
    for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr) {
        g[*eItr].visited = false;
    }
        
}

bool isCyclic(Graph &g) {
    stack<Graph::vertex_descriptor> s;
    int numVerticies = num_vertices(g);
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    
    s.push(*(vItrRange.first));
    int nodeCount = 0;
    
    
    //If there is a neighboring node that is visited AND not its parent, there is a cycle
    while (!s.empty()) {
        Graph::vertex_descriptor v = s.top();
        s.pop();
        
        
        if (!(g[v].visited)) {
            g[v].visited = true;
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange2 = adjacent_vertices(v, g);
            
            for (Graph::adjacency_iterator vItr= vItrRange2.first; vItr != vItrRange2.second; ++vItr) {
                if (g[*vItr].visited == true && *vItr != g[v].pred) {
                    return true;
                }
                
                
                if (!g[*vItr].visited) {
                    g[*vItr].pred = v;
                    s.push(*vItr);
                }
               
            }
        }
    }
    
    return false;
}

Graph::vertex_descriptor findUnvisitedNode(Graph &g) {
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    
    for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
        if (!g[*vItr].visited) {
            return *vItr;
        }
    }
    return -1;
}


//BFS on each unvisited node. add the edges you traverse to the graph to return
void findSpanningForest(Graph &g, Graph &sf) {
    queue<Graph::vertex_descriptor> q;
    
    
    //While there are still unvisited nodes
    Graph::vertex_descriptor currentStartNode = findUnvisitedNode(g);
    q.push(currentStartNode);
    while (currentStartNode != -1) {
        //Perform a bfs on this node, while adding every edge and node to sf
        while (!q.empty()) {
            
            Graph::vertex_descriptor v = q.front();
            g[v].visited = true;
            q.pop();
            add_vertex(g[v], sf);
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange2 = adjacent_vertices(v, g);
            
            // Loop over adjacent nodes in the graph
            for (Graph::adjacency_iterator vItr= vItrRange2.first; vItr != vItrRange2.second; ++vItr) {
                if (!g[*vItr].visited) {
                    q.push(*vItr);
                    
                    pair<Graph::edge_descriptor, bool> checkEdge = edge(v, *vItr,sf);
                    if (!checkEdge.second) {
                        EdgeProperties p = g[edge(v, *vItr, g).first];
                        add_edge(v, *vItr, p, sf);
                    }
                }
            }
        }
        currentStartNode = findUnvisitedNode(g);
        q.push(currentStartNode);
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
    string tempFileName = "";
    //cout << "Enter in a file path for the graph (Note, if this doesn't work for you, you can also try to manually put the file path in line 252 of main) : ";
    //cin >> tempFileName;
    
    
    //IF FILE PATH INPUT DOESN'T WORK, REPLACE "tempFileName" BELOW WITH A STRING FOR THE FULL FILE PATH,
    //AND COMMENT OUT THE LINE ABOVE ("cin >> tempFileName")
    //EX: string fileName = "/Users/Gurtaj/Dropbox/College Work/Middler/Algorithms/Project5c/Project5b/graph/graph6.txt"
    //-----------------------------------------------------------------------------------------------------------
    string fileName = "/Users/Gurtaj/Dropbox/College Work/Middler/Algorithms/Project6a/Project5b/graph/graph4.txt";
    //--------------------------------------------------------------------------------------------------------------

    
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << "Please make sure to replace the file path on line 260." << endl;
        exit(1);
    }


    
    
    Graph g;
    Graph::vertex_descriptor start = 0;
    Graph::vertex_descriptor end = 6;
    
    initializeGraph(g, start, end, fin);
    cout << endl;
    resetVisited(g);
    cout << "Is Connected: " << isConnected(g) << endl;
    cout << endl;
    
    resetVisited(g);
    cout << "Is Cyclic: " << isCyclic(g) << endl;
    resetVisited(g);
    cout << endl;
    cout << "Edges in Spanning Forest" << endl;
    Graph minSpan;
    findSpanningForest(g, minSpan);
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(minSpan);
    int totalWeight = 0;
    vector<Graph::vertex_descriptor> connectedComp;
    // Loop over all edges in the graph
    for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr) {
        totalWeight += g[*eItr].weight;
        if (!(find(connectedComp.begin(), connectedComp.end(), source(*eItr,minSpan)) != connectedComp.end())) {
            connectedComp.push_back(source(*eItr,minSpan));
        }
        if (!(find(connectedComp.begin(), connectedComp.end(), target(*eItr,minSpan)) != connectedComp.end())) {
            connectedComp.push_back(target(*eItr,minSpan));
        }
        cout << source(*eItr, minSpan) << " -> " << target(*eItr, minSpan) << endl;
    }
    
    cout << endl;
    
    cout << "Total Weight: " << totalWeight << endl;
    cout << "Number of Connected Componenets: " << connectedComp.size() << endl;
    
    
    cout << "Done" << endl;
    fin.close();
}
