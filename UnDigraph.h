// by Adam Mullins, adam.l.m@gmail.com
#ifndef UNDIGRAPH_H
#define UNDIGRAPH_H

class UnDigraph {
 private:
  int n_; // n is the number of verticies in the graph.
  bool **matrix_;

  void depthFirstSearch(int v, bool* explored);
 public:
  UnDigraph(int num_verticies);
  UnDigraph(const UnDigraph& other);
  ~UnDigraph();

  void addEdge(int u, int v);
  void removeEdge(int u, int v);
  int totalEdges();
  int degree(int v);
  void printEdges();

  bool isAdjacent(int u, int v);
  bool isConnected(int v);

  int depthFirstSearch(int v);
};
    
#endif // #ifndef UNDIGRAPH_H
