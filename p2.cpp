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
#include <boost/graph/graphviz.hpp>

#include "path_count.hpp"

using namespace boost;

const char* NAME = "MNPQUOTSRYVXWZ";

int main(int,char*[])
{
  std::cout << "  ######\n";
  std::cout << " # p2 # \n";
  std::cout << "######  \n";

  // create a typedef for the Graph type
  typedef adjacency_list<vecS, vecS, directedS> Graph;
  
  // Make convenient labels for the vertices
  enum { M, N, P, Q, U, O, T, S, R, Y, V, X, W, Z, A };
  const int num_vertices = A;

  // writing out the edges in the graph
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

  // declare a graph object
  Graph g(num_vertices);

  // add the edges to the graph object
  for (int i = 0; i < num_edges; ++i)
    add_edge(edge_array[i].first, edge_array[i].second, g);

  std::ofstream fout;
  fout.open("mygraph.dot");
  write_graphviz(fout, g, make_label_writer(NAME));
  write_graphviz(std::cout, g, make_label_writer(NAME));
    
  dynamic_properties dp;
  //dp.property("node_id", get(vertex_name, g));

  std::string filename = "mygraph.dot";
  std::ifstream fin;
  fin.open(filename.c_str());
  

  //read_graphviz(fin, g, dp);

  return 0;
}