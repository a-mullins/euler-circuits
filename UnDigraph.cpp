// by Adam Mullins, adam.l.m@gmail.com
#include <iostream>
#include "UnDigraph.h"

using std::cout;
using std::endl;

UnDigraph::UnDigraph(int num_verticies) {
  n_ = num_verticies;

  matrix_ = new bool*[ n_ ];

  for(int i = 0; i < n_; ++i)
    matrix_[i] = new bool[ (i+1) ];

  // init vals, just in case.
  for(int row = 0; row<n_; row++) {
    for(int col = 0; col<(row+1); col++) {
      matrix_[row][col] = 0;
    }
  }
}


// Deep copy constructor.
UnDigraph::UnDigraph(const UnDigraph& other) {
  n_ = other.n_;

  matrix_ = new bool*[ n_ ];

  for(int i = 0; i < n_; ++i)
    matrix_[i] = new bool[ (i+1) ];

  // init vals, pulling from other.
  for(int row = 0; row<n_; row++) {
    for(int col = 0; col<(row+1); col++) {
      matrix_[row][col] = other.matrix_[row][col];
    }
  }
}


UnDigraph::~UnDigraph() {
  for(int i = 0; i < n_; i++) {
    delete [] matrix_[i];
  }

  delete [] matrix_;
}

void UnDigraph::addEdge(int u, int v) {
  if( u < n_ && v < n_ ) {
    if( u > v )
      matrix_[u][v] = true;
    else 
      matrix_[v][u] = true;
  }
}

void UnDigraph::removeEdge(int u, int v) {
  if( u < n_ && v < n_ ) {
    if( u > v )
      matrix_[u][v] = false;
    else 
      matrix_[v][u] = false;
  }
}

bool UnDigraph::isAdjacent(int u, int v) {
  if( u < n_ && v < n_ ) {
    if( u > v )
      return matrix_[u][v];
    else 
      return matrix_[v][u];
  }
}

// bool* UnDigraph::adjacentVertices(int v) {
//   bool* list = new bool[n_];

//   for(int i=0; i<n_; i++) {
//     list[i] = isAdjacent(i, v);
//   }

//   return list;
// }

void UnDigraph::printEdges() {
  // traverse matrix. if row, col is true, then u, v are connected.
  for(int row = 0; row<n_; row++) {
    for(int col = 0; col<(row+1); col++) {
      if( matrix_[row][col] == true ) {
	cout << "(" << row << "," << col << ") ";
      }
    }
  }
  cout << endl;
}  

// returns the number of vertices visited.
// note that if v is connected, then depthFirstSearch(v) == n_
int UnDigraph::depthFirstSearch(int v) {
  if( v < n_ ) {
    bool explored[n_];
    for(int i=0; i<n_; i++) { explored[i] = false; }

    depthFirstSearch(v, explored);

    int sum = 0;
    for(int i = 0; i<n_; i++)
      if( explored[i] )
	sum++;

    return sum;
  }
  return 0;
}

// preform dfs beginning at v.
void UnDigraph::depthFirstSearch(int cur, bool* explored) {
  // label me as explored & visit.
  explored[cur] = true;
  //cout << "Visiting vertex " << cur << endl;

  // for every unexplored vertex adjacent to this one:
  for(int next=0; next<n_; next++) {
    if( isAdjacent(cur, next) && !(explored[next]) )
      depthFirstSearch(next, explored);
  }  

  return;
}

bool UnDigraph::isConnected(int v) {
  return (n_ == depthFirstSearch(v));
}

// count up all the edges in the graph
int UnDigraph::totalEdges() {
  // traverse the matrix.
  // if a field is true, then it is an edge and adds to sum.
  int sum = 0;

  for(int row = 0; row<n_; row++) {
    for(int col = 0; col<(row+1); col++) {
      if( matrix_[row][col] == true ) {
	sum++;
      }
    }
  }

  return sum;
}

// count up all the edges leading from this particular vertex.
int UnDigraph::degree(int v) {
  int sum = 0;

  for(int i=0; i<n_; i++) {
    if( isAdjacent(i, v) )
      sum++;
  }

  return sum;
}
