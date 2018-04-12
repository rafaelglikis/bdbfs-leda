#ifndef BDBFS_H
#define BDBFS_H

#include <LEDA/graph/graph.h>
#include <LEDA/graph/basic_graph_alg.h>
#include <list>
#include <queue>
#include <unordered_set>

namespace bdbfs
{
    leda::node bdBFS(leda::graph&, leda::node&, leda::node&, 
        leda::node_array<leda::edge>&, leda::node_array<leda::edge>&);
    void headStep(leda::graph&, leda::node_array<bool>&, leda::node_array<bool>&, 
        std::deque<leda::node>&, leda::node_array<leda::edge>&, leda::node&);
    void tailStep(leda::graph&, leda::node_array<bool>&, leda::node_array<bool>&,
        std::deque<leda::node>&, leda::node_array<leda::edge>&, leda::node&);

    std::list<leda::edge> shortestPath(leda::graph&, leda::node&, leda::node&);
    
    
    void printInfo(leda::graph&, leda::node_array<leda::edge>&, leda::node_array<leda::edge>&, leda::node&, leda::node&, leda::node&);
}

#endif