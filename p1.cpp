/**
 *
 * CSCE-622: Generic Programming -- Assignment 3
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 1, 2010
 */

#include <iostream>
#include <exception>
#include <string>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graphviz.hpp>

#include "path_count.hpp"

using namespace boost;

const char* NAME = "MNPQUOTSRYVXWZ";

int main(int,char*[])
{
  std::cout << "  ######\n";
  std::cout << " # p1 # \n";
  std::cout << "######  \n";

  // Create a graph (same as in p1.cpp)
  std::cout << "\n[+] building the graph shown in assignment 3 \n";
  typedef adjacency_list<vecS, vecS, directedS> Graph;
  enum { M, N, P, Q, U, O, T, S, R, Y, V, X, W, Z, A };
  const int num_vertices = A;
  typedef std::pair<int, int> Edge;
  Edge edge_array[] = 
  { Edge(M,X), Edge(M,R), Edge(M,Q),
    Edge(N,Q), Edge(N,U), Edge(N,O),
    Edge(P,O), Edge(P,S), Edge(P,Z),
    Edge(Q,T), Edge(U,T),
    Edge(O,R), Edge(O,V), Edge(O,S),
    Edge(S,R), Edge(R,Y), Edge(Y,V),
    Edge(V,X), Edge(V,W), Edge(W,Z) };
  const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);
  Graph g(num_vertices);
  for (int i = 0; i < num_edges; ++i)
    add_edge(edge_array[i].first, edge_array[i].second, g);

  // Test the algorithm path_count() on the graph
  std::cout << "\n[+] applying the algorithm path_count() to the graph \n";

  std::cout << "path_count(g, P, V) -> ";
  std::cout << path_count(g, P, V) << std::endl;

  std::cout << "path_count(g, N, Y) -> ";
  std::cout << path_count(g, N, Y) << std::endl;

  std::cout << "path_count(g, M, S) -> ";
  std::cout << path_count(g, M, S) << std::endl;

  std::cout << "path_count(g, R, X) -> ";
  std::cout << path_count(g, R, X) << std::endl;

  std::cout << "path_count(g, X, X) -> ";
  std::cout << path_count(g, X, X) << std::endl;

  // Print the graph to a file
  std::cout << "\n[+] printing g to a file \n";
  std::string filename = "mygraph.dot";
  std::ofstream fout;
  fout.open(filename.c_str());
  write_graphviz(fout, g);
  // uncomment following line to print to the screen
  //write_graphviz(std::cout, g, make_label_writer(NAME));
  fout.close();

  return 0;
}
