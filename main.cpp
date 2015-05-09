// by Adam Mullins, adam.l.m@gmail.com
//
// Generate all Euler circuits on the complete graph of five
// verticies.
//
// By default, only circuits on one vertex are found, but
// providing the -a switch will find all circuits on all verticies.
// 
// The circuits are written to stdout, one circuit per line.
#include <iostream>
#include <sstream>
#include <string>
#include "UnDigraph.h"

using std::cout;
using std::endl;
using std::string;

const int SIZE = 5;
const char* NAME = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void build_paths(int v, UnDigraph &g, const string &path);
 
int main(int argc, char* argv[]) {
  bool circuitsOnSingle = true;
  for(int i=0; i<argc; i++) {
    if( string(argv[i]) == "-a" || string(argv[i]) == "--all-circuits" )
      circuitsOnSingle = false;
  }


  UnDigraph g(SIZE);

  // Make the graph complete.
  // That is, connect every vertex to every other vertex, but not itself.
  for(int i = 0; i<SIZE; i++) {
    for(int j=(i+1); j<SIZE; j++) {
      g.addEdge(i, j);
    }
  }


  if(circuitsOnSingle) {
    build_paths(0, g, "");
  } else {
    for(int i=0; i<SIZE; i++ ) { build_paths(i, g, ""); }
  } 


  return 0;
}

// This algorithm is similar to a DFS, except it also builds the tree
// as it goes. It transforms a graph into a tree, where each node
// represents the 'path so far'. Each leaf of the graph would
// represent a path through the graph that satisifies our criteria; in
// this case, that the path is an Euler circuit.
//
// Notice that the tree itself is never stored (outside of the stack),
// we just call build_paths recursively until we get a leaf, then
// print the leaf and backtrack.
void build_paths(int v, UnDigraph  &g, const string &path) {
  // 0. create a local copy of path.
  string s(path);

  // 1. visit.
  s.append(1, NAME[v]);
  
  // 2. an empty edgeset means we have found an Euler circuit. therefore:
  //    if edgeset is empty, print path, return.
  if( g.totalEdges() == 0 ) { cout << s << endl; return; }

  // 3. traverse every edge incident on v.
  for(int other=0; other<SIZE; other++) {
    if( g.isAdjacent(v, other) ) {
      UnDigraph g2(g);
      
      g2.removeEdge(v, other);

      build_paths(other, g2, s);
    }
  }
}
