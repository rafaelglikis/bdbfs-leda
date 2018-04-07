#ifndef BFS_H
#define BFS_H

#include <LEDA/graph/graph.h>
#include <LEDA/graph/basic_graph_alg.h>
#include <list>
#include <queue>
#include <unordered_set>

std::list<leda::edge> ledaShortestPathBFS(leda::graph&, leda::node&, leda::node&); 
std::list<leda::edge> bdBFS(leda::graph&, leda::node&, leda::node&);

#endif