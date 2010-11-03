/**
 *
 * CSCE-622: Generic Programming -- Assignment 3
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 2, 2010
 */

#include <iostream>
#include <exception>
#include <string>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <cstdlib>

#include "path_count.hpp"

using namespace boost;

int NUMBER_OF_PAIRS_SOURCE_TARGET = 1;

int main(int argc,char* argv[])
{
  std::cout << "  ######\n";
  std::cout << " # p3 # \n";
  std::cout << "######  \n";

  if (argc > 1)
    NUMBER_OF_PAIRS_SOURCE_TARGET = atof(argv[1]);

  // generate random directed graph
  typedef adjacency_list<vecS, vecS, directedS> Graph;
  Graph g;
  int number_vertices = 10;
  int number_edges = 13;
  bool allow_parallel = false;
  bool self_edges = false;
  std::cout << "Vertices number: " << number_vertices << std::endl;
  std::cout << "Edges number: " << number_edges << std::endl;
  mt19937 random_number_generator;
  generate_random_graph(g, number_vertices, number_edges,
                        random_number_generator, allow_parallel, self_edges);

  property_map<Graph, vertex_index_t>::type index = get(vertex_index, g);
                              
  // print graph to the screen
  std::cout << "\n[+] random generation of a graph" << std::endl;

  std::cout << "Vertice list: ";
  graph_traits<Graph>::vertex_iterator vi, vi_end;
  for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
    std::cout << index[*vi] <<  " ";
  std::cout << std::endl;

  std::cout << "Edge list: ";
  graph_traits<Graph>::edge_iterator ei, ei_end;
  for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    std::cout << "(" << index[source(*ei, g)] 
              << "," << index[target(*ei, g)] << ") ";
  std::cout << std::endl;

  // print graph in dot format to a file 
  std::string filename = "randomgraph.dot";
  std::ofstream fout;
  fout.open(filename.c_str());
  boost::write_graphviz(fout, g);
  fout.close();

  // randomly select source and target vertices and apply path_count()
  typedef graph_traits<Graph>::vertex_descriptor Vertex;
  Vertex source, target;
  for (int i = 0; i < NUMBER_OF_PAIRS_SOURCE_TARGET; i++) {
    std::cout << "\n[+] random selection of a pair of vertices #" << i+1 << std::endl;

    source = random_vertex(g, random_number_generator);
    target = random_vertex(g, random_number_generator);
    std::cout << "randomly selected source: ";
    std::cout << index[source] <<  "\n";
    std::cout << "randomly selected target: ";
    std::cout << index[target] <<  "\n";
  
    std::cout << "apply path_count() between source and target: ";
    std::cout << path_count(g, source, target) << "\n\n";
  }

  return 0;
}
