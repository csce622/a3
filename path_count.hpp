/**
 *
 * graph_count.hpp
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 1, 2010
 */

#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <exception>

using namespace boost;

template <typename Vertex>
class path_counter_visitor : public default_dfs_visitor {
public:
  path_counter_visitor() {}
  path_counter_visitor(Vertex s, Vertex t) : mysource(s), mytarget(t), mycount() {}

  template <typename Graph>
  void discover_vertex(Vertex u, const Graph& g) {
    typedef typename graph_traits<Graph>::out_edge_iterator Iter;
    Iter ei, ei_end;
    tie(ei, ei_end) = out_edges(u, g);
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

