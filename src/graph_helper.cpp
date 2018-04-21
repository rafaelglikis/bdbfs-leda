#include "../incl/graph_helper.h"

leda::graph gridGraphCreator(int x, int y)
{
    leda::graph G;
    leda::grid_graph(G, x);
    
    for(int j=0; j<y/x-1; ++j){
        leda::graph g1;
        leda::grid_graph(g1, x);

        leda::node u = G.last_node();
        leda::node v = g1.first_node();

        for(int i=0; i<(x-1); ++i) {
            u = G.pred_node(u);
        }

        G.join(g1);

        for(int i=0; i<x; ++i){
            G.new_edge(u,v);
            u = G.succ_node(u);
            v = G.succ_node(v);
        }

    }

    return G;
}