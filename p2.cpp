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

using namespace boost;

const char* NAME = "MNPQUOTSRYVXWZ";

int main(int,char*[])
{
  std::cout << "  ######\n";
  std::cout << " # p2 # \n";
  std::cout << "######  \n";
    
  typedef property < vertex_name_t, std::string, property < vertex_color_t, float > > vertex_p;  
  typedef property < edge_weight_t, double > edge_p;
  typedef property < graph_name_t, std::string > graph_p;
  typedef adjacency_list < vecS, vecS, directedS, vertex_p, edge_p, graph_p > graph_t;
 
  // Create a graph (same as in p1.cpp)
  std::cout << "\n[+] building a graph \n";
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
  graph_t g(num_vertices);
  for (int i = 0; i < num_edges; ++i)
    add_edge(edge_array[i].first, edge_array[i].second, g);

    
    
  // Print the graph to a file
  std::cout << "\n[+] printing g to a file \n";
  std::ofstream fout;
  fout.open("mygraph.dot");
  write_graphviz(fout, g);
  // uncomment following line to print to the screen
  //write_graphviz(std::cout, g, make_label_writer(NAME));
  fout.close();

    
    
  // Erase the content of the graph
  std::cout << "\n[+] clearing g \n";
  g.clear();

    
    
  // Open and read graph from a file
  std::cout << "\n[+] reading g again from the file \n";
  std::string filename = "mygraph.dot";
  std::ifstream fin;
  fin.open(filename.c_str());
  dynamic_properties dp;
  dp.property("node_id", get(vertex_name, g));
  read_graphviz(fin, g, dp);

    
    
  // Check graph read correctly
  std::cout << "\n[+] checking g \n";
  property_map<graph_t, vertex_index_t>::type index = get(vertex_index, g);
    
  std::cout << "Vertice list: ";
  graph_traits<graph_t>::vertex_iterator vi, vi_end;
  for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
    std::cout << NAME[index[*vi]] <<  " ";
  std::cout << std::endl;
    
  std::cout << "Edge list: ";
  graph_traits<graph_t>::edge_iterator ei, ei_end;
  for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    std::cout << "(" << NAME[index[source(*ei, g)]] 
                     << "->" << NAME[index[target(*ei, g)]] << ") ";
  std::cout << std::endl;
    
  return 0;
}
