#ifndef BFS_H
#define BFS_H

#include <LEDA/graph/graph.h>
#include <LEDA/graph/basic_graph_alg.h>
#include <list>
#include <queue>
#include <unordered_set>

std::list<leda::edge> shortestPathBFS(leda::graph&, leda::node&, leda::node&); 
std::list<leda::edge> shortestPathbdBFS(leda::graph&, leda::node&, leda::node&);
std::list<leda::edge> bdBFS(leda::graph &G, leda::node &source, leda::node &target);
std::list<leda::edge> shortestPath(leda::graph&, leda::node&, leda::node&, leda::node_array<leda::edge>&);

#endif