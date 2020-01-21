#include <iostream>

#include "timestamp.h"

#ifndef UGRAPH_H
#define UGRAPH_H
using namespace std;

struct edge { 
  int neighbor;
  int w;
  edge() {neighbor = 0; w = 0;} 
  edge(int i, int j) {neighbor = i; w = j;} 
};

class Ugraph { 

  public:
    Ugraph(int N); 
    void addEdge(int u, int v);
    void bfs(int s);
    void pathbfs(int s);
    void printGraph();
    bool distinctPaths(int u, int v); 
    void getPath(int v, vector<int> &path);
    void printParents();
    void setWeight(int v);
    void clearWeight();
    void removeEdge(int u, int v);
    //void printPath(int v);
    void dfsVisit(int u, int &t);
    void dfs();
    bool twoColoring();
    bool cycleVisit(int u, int &t);
    void printCC();
    //void ccDfs(int &id, vector<int> &cc);
    void ccVisit(int u, vector<int> &cc, int id);
    void printBridges();
    void bridgeVisit(int u, int &t, vector<int> &low);
   
  private:
    vector<vector <edge> > Adj;
    vector<int> parent;  //for BFS
    vector<int> distance;  //for BFS and DFS
    vector<char> colors; //for DFS
    vector<TimeStamp> stamps; //for DFS
    int size;  //total vertices
    //vector<int> low;
};

#endif
