#ifndef BFS_H
#define BFS_H

#include <LEDA/graph/graph.h>
#include <LEDA/graph/basic_graph_alg.h>
#include <list>
#include <queue>
#include <unordered_set>

namespace bfs 
{
    std::list<leda::edge> shortestPath(leda::graph&, leda::node&, leda::node&); 
    void printInfo(leda::graph&, leda::node_array<int>&, leda::node_array<leda::edge>&, leda::node&, leda::node&);
}

#endif