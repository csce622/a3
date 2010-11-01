/**
 *
 * CSCE-622: Generic Programming -- Assignment 3
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 1, 2010
 */

#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <exception>

using namespace boost;

const char* NAME = "MNPQUOTSRYVXWZ";

template <typename Vertex>
class path_counter_visitor : public default_dfs_visitor {
public:
  path_counter_visitor() {}
  path_counter_visitor(Vertex s, Vertex t) : mysource(s), mytarget(t), mycount() {}

  template <typename Graph>
  void discover_vertex(Vertex u, const Graph& g) {
    typedef typename graph_traits<Graph>::out_edge_iterator Iter;
    //typedef typename property_map<Graph, vertex_index_t>::type IndexMap;
    Iter ei, ei_end;
    tie(ei, ei_end) = out_edges(u, g);
    //IndexMap index = get(vertex_index, g);
    //std::cout<<"discover_vertex "<<NAME[index[u]]<<std::endl;
    if (u == mytarget) {
      while (ei != ei_end) {
        Vertex v = target(*ei, g);
        finish_vertex(v, g);
        ++ei;
      }
      mycount[u] = 1;
    }
    else {
      mycount[u] = 0;
    }
  }

  template <typename Graph>
  void finish_vertex(Vertex u, const Graph& g) {
    typedef typename graph_traits<Graph>::out_edge_iterator Iter;
    Iter ei, ei_end;
    tie(ei, ei_end) = out_edges(u,g);
    while (ei != ei_end) {
      Vertex v = target(*ei, g);
      mycount[u] += mycount[v];
      ++ei;
    }
    if (u == mysource) {
      throw mycount[u];
    }
  }

private:
  std::map<int, Vertex> mycount;
  Vertex mysource;
  Vertex mytarget;
};

template <typename Graph> 
typename graph_traits<Graph>::edges_size_type 
path_count(Graph& g, 
           typename graph_traits<Graph>::vertex_descriptor s, 
           typename graph_traits<Graph>::vertex_descriptor t)
{
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  try {
    path_counter_visitor<Vertex> vis(s, t);  
    depth_first_search(g, visitor(vis).root_vertex(s));
  }
  catch (typename graph_traits<Graph>::edges_size_type count) {
//    std::cout << "number of paths is " << count << std::endl; 
    return count;
  }
}


int main(int,char*[])
{
  std::cout << "  ######\n";
  std::cout << " # p1 # \n";
  std::cout << "######  \n";

  // create a typedef for the Graph type
  typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;

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

  std::cout << "path_count(g, P, V) -> ";
  std::cout << path_count(g, P, V) << std::endl;

  std::cout << "path_count(g, N, Y) -> ";
  std::cout << path_count(g, N, Y) << std::endl;

  std::cout << "path_count(g, M, S) -> ";
  std::cout << path_count(g, M, S) << std::endl;

  std::cout << "path_count(g, R, X) -> ";
  std::cout << path_count(g, R, X) << std::endl;

  return 0;
}
