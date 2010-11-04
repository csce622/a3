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
    
  std::cout << "\nWARNING: you need to run p1 before p2 to generate the file the graph is read from) \n";

  typedef property < vertex_name_t, std::string, property < vertex_color_t, float > > vertex_p;  
  typedef property < edge_weight_t, double > edge_p;
  typedef property < graph_name_t, std::string > graph_p;
  typedef adjacency_list < vecS, vecS, directedS, vertex_p, edge_p, graph_p > graph_t;
    
  // Open and read graph from a file
  std::cout << "\n[+] reading graph from a file \n";
  std::string filename = "mygraph.dot";
  std::ifstream fin;
  fin.open(filename.c_str());
  graph_t g(0);
  dynamic_properties dp;
  dp.property("node_id", get(vertex_name, g));
  read_graphviz(fin, g, dp);

    
  // Check graph read correctly
  /*
  std::cout << "\n[+] printing the graph to the screen \n";
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
  */

  write_graphviz(std::cout, g, make_label_writer(NAME));
                        
  // Apply path_count()
  std::cout << "\n[+] applying the algorithm path_count() to the graph \n";
  enum { M, N, P, Q, U, O, T, S, R, Y, V, X, W, Z, A };


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

  return 0;
}
