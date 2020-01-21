#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>
#include <utility>
#include <vector>

using namespace std;

#include "ugraph.h"

Ugraph::Ugraph (int N) {
  Adj.resize(N);
  parent.resize(N);
  stamps.resize(N);
  distance.resize(N);
  colors.resize(N);
  //low.resize(N);
  size = N;
  for (int i = 0; i < size; i++) { 
    parent[i] = i;
    colors[i] = 'W';
    distance[i] = INT_MAX;
    //low[i] = -1;
  } 
}

void Ugraph::addEdge(int u, int v) {
  edge e(v , 0);
  Adj[u].push_back(e);
  
  edge d(u, 0);
  Adj[v].push_back(d);
}

void Ugraph::removeEdge(int u, int v) { 
  for (int i = 0; i < Adj[u].size(); i++) {
    if (Adj[u][i].neighbor == v) { 
      Adj[u][i] = Adj[u][Adj[u].size() - 1];
      Adj[u].resize(Adj[u].size() - 1);
    } 
  } 
  for (int i = 0; i < Adj[v].size(); i++) { 
    if (Adj[v][i].neighbor == u) {
      Adj[v][i] = Adj[v][Adj[v].size() - 1];
      Adj[v].resize(Adj[v].size() - 1);
    } 
  } 
}
void Ugraph::printGraph() { 
  for (int i = 0; i < Adj.size(); i++) {
    for (int n = 0; n < Adj[i].size(); n++) {
      cout << Adj[i][n].neighbor << " ";
    } cout << '\n';
  } 
} 

bool Ugraph::distinctPaths(int u, int v) {
  pathbfs(u);
  if (distance[v] == INT_MAX) {
    clearWeight();
    return false;
  }
  setWeight(v);
  vector<int> path1;
  vector<int> path2;
  getPath(v, path1);
  pathbfs(u);
  if (distance[v] == INT_MAX) {
    clearWeight();
    return false;
  }
  getPath(v, path2);
  for (int i = 0; i < path1.size(); i++)
    cout << path1[i] << " ";
  cout << '\n';
  for (int k = 0; k < path2.size(); k++) 
    cout << path2[k] << " ";
  cout << '\n';
clearWeight();
return true;
}  

void Ugraph::pathbfs(int s) { 
  for (int i = 0; i < size; i++) {
    parent[i] =i;
    distance[i] =INT_MAX;
  }
  queue<int> q;
  distance[s] = 0;
  int u = 0;
  q.push(s);
  while(!q.empty()) { 
    u = q.front();
    q.pop();
    for (int i = 0; i < Adj[u].size(); i++) { 
      int v = Adj[u][i].neighbor;
      if (distance[v] == INT_MAX) { 
        if (Adj[u][i].w != 1) {
          //Adj[u][i].w = 1;
          distance[v] = distance[u] + 1;
          parent[v] = u;
          q.push(v);  
        }
      }
    }
  } 
}
//u != v recurisve else push return
void Ugraph::getPath(int v, vector<int> &path) {
  if (v == parent[v]) {
    path.push_back(v);
    return;
  } 
  getPath(parent[v], path);
  path.push_back(v);
}

void Ugraph::setWeight(int v) {
  int p = parent[v];
  if (v == p)
    return;

  for (int i = 0; i < Adj[p].size(); i++) {
    if (Adj[p][i].neighbor == v)
      Adj[p][i].w = 1;
  } 
  
  for (int i = 0; i < Adj[v].size(); i++) {
    if (Adj[v][i].neighbor == p)
      Adj[v][i].w = 1;
  }
  setWeight(parent[v]);  
}  

void Ugraph::clearWeight() {
  for (int i = 0; i < Adj.size(); i++) {
    for (int n = 0; n < Adj[i].size(); n++) {
      Adj[i][n].w = 0;
    } 
  }
}

void Ugraph::bfs(int s) { 
  queue<int> q;
  distance[s] = 0;
  int u = 0;
  q.push(s);
  while(!q.empty()) { 
    u = q.front();
    q.pop();
    cout << u << " ";
    
    for (int i = 0; i < Adj[u].size(); i++) { 
      int v = Adj[u][i].neighbor;
      if (distance[v] == INT_MAX) { 
        distance[v] = distance[u] + 1;
        parent[v] = u;
        q.push(v);  
      }
    }
  } 
  for (int i = 0; i < size; i++) {
    parent[i] = i;
    distance[i] = INT_MAX;
  } 
cout << '\n';  
}

void Ugraph::dfsVisit(int u, int &t) {
  cout << u << " ";
  colors[u] = 'G';
  stamps[u].d = t;   //distance time of u
  t++;
  for (int i = 0; i < (int) Adj[u].size(); i++) { 
    int child = Adj[u][i].neighbor;
    if (colors[child] == 'W') { 
      parent[child] = u;
      dfsVisit(child, t);
    } 
  } 
  stamps[u].f = t;   //finish time is put into stamps
  t++;
  colors[u] = 'B';
  
} 

void Ugraph::dfs() { 
  int t = 0;
  for (int i = 0; i < size; i++) { 
    colors[i] = 'W';
    parent[i] = i;
  } 
  for (int i = 0; i < size; i++) { 
    if (colors[i] == 'W') 
      dfsVisit(i, t);//t is passed by reference
  } 
 cout << '\n';
}

bool Ugraph::twoColoring() {
  bool cycleOdd = false;
  int t = 0;
  for (int i = 0; i < size; i++) {
    colors[i] = 'W';
  } 
  for (int i = 0; i < size; i++) {
    if (colors[i] == 'W') {
      cycleOdd = cycleVisit(i, t);
      if (!cycleOdd)
        return false;
    }
  } 
  return true;
} 

bool Ugraph::cycleVisit(int u, int &t) {
  colors[u] = 'G';
  stamps[u].d = t;
  t++;
  for (int i = 0; i < Adj[u].size(); i++) {
    int child = Adj[u][i].neighbor;
    if (colors[child] == 'W')
      cycleVisit(child, t);
  
    if ((stamps[u].d - stamps[child].d) % 2 == 0)
      return false;
  } 
  stamps[u].f = t;
  t++;
  colors[u] = 'B';
return true;
} 

void Ugraph::printParents() {
  for (int i = 0; i < parent.size(); i++) 
    cout << parent[i] << " ";

  cout << '\n';
} 

void Ugraph::printCC() {
  vector <int> cc;
  cc.resize(size);
  for (int i = 0; i < size; i++) {
    cc[i] = -1;
    colors[i] = 'W';
    parent[i] = i;
  } 
  int id = 0;
  for (int i = 0; i < size; i++) { 
    if (colors[i] == 'W') { 
      ccVisit(i, cc, id);
      id++;
    }   
  }
  vector< vector <int> > twoDcc;
  twoDcc.resize(id);
  for (int i = 0; i < cc.size(); i++) { 
    twoDcc[cc[i]].push_back(i);
  }
  for (int i = 0; i < twoDcc.size(); i++) {
    for (int k = 0; k < twoDcc[i].size(); k++) { 
      cout << twoDcc[i][k] << " ";
    } 
    cout << '\n';
  } 
} 

void Ugraph::ccVisit(int u, vector<int> &cc, int id) {
  cc[u] = id; 
  colors[u] = 'G';
  for (int i = 0; i < Adj[u].size(); i++) { 
    int child = Adj[u][i].neighbor;
    if (colors[child] == 'W') {
      parent[child] = u;
      ccVisit(child, cc, id);
    } 
  }
  colors[u] = 'B';
}

void Ugraph::printBridges() {
  vector<int> low (size, 0);
  int t = 0;
  for (int i = 0; i < size; i++) { 
    colors[i] = 'W';
    parent[i] = i;
  } 
  for (int i = 0; i < size; i++) { 
    if (colors[i] == 'W')
      bridgeVisit(i, t, low);
      
  } 
}

void Ugraph::bridgeVisit(int u, int &t, vector<int> &low) {
  colors[u] = 'G';
  stamps[u].d = t;
  low[u] = stamps[u].d;//t;//added
  t++;
  for (int i = 0; i < Adj[u].size(); i++) { 
    int child = Adj[u][i].neighbor; 
    if (colors[child] == 'W') { 
      parent[child] = u;
      bridgeVisit(child, t, low);
      low[u] = min(low[u], low[child]);
      if (stamps[child].d == low[child]) { 
        cout << u << " " << child << endl;
      } 
    }    
    else if (child != parent[u]) {
      low[u] = min(low[u], stamps[child].d);
    }
  }    
  stamps[u].f = t;
  t++;
  colors[u] = 'B';
}









 
