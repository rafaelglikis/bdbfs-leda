#include "bfs.h"

namespace bfs
{
    /**
     * Finds the shortest path by running leda's BFS implementation
    */
    std::list<leda::edge> shortestPath(leda::graph &G, leda::node &source, leda::node &target) 
    {
        // Running BFS
        leda::node_array<int> dist(G,-1); // The distance from source to nodes v in G
        leda::node_array<leda::edge> pred(G); // Pred contains the edge that was used by BFS to reach v or nil, for every node v of G.
        BFS(G,source,dist,pred);

        #ifdef INFO
        printInfo(G, dist, pred, source, target);
        #endif

        std::list<leda::edge> path; // Contains every edge of shortest path from source to target

        // if target not descovered return empty path
        if (pred[target]==nil) {
            #ifdef INFO
            std::cout << "[i] Graph not strongly coherent." << std::endl;
            #endif
            return path;
        }
        
        // Find the shortest path from pred (O(number_of_edges))
        leda::node checkpoint = target;
        while (checkpoint != source) {
            path.push_front(pred[checkpoint]);
            checkpoint = G.source(pred[checkpoint]);
        }
        
        return path;
    }

    /**
     * Prints the result of the algorithm.
    */
    void printInfo(leda::graph& G, leda::node_array<int>& dist, leda::node_array<leda::edge>& pred,  leda::node &source, leda::node &target)
    {
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "|\t L E D A  B F S  I N F O\t|" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "| * Source:  ";
        G.print_node(source);
        std::cout << "\t\t\t|" << std::endl << "| * Target:  ";
        G.print_node(target);
        std::cout << "\t\t\t|" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "|node\t" << "|    distance\t" << "| shortest-path |" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        leda::node v;
        forall_nodes(v,G) {
            std::cout << "| ";
            G.print_node(v);
            std::cout << "\t|\t" << dist[v] << "\t| ";
            if (pred[v]!=nil) G.print_edge(pred[v]);
            else std::cout << "\t";
            std::cout << "\t|" << std::endl;
        }
        std::cout << "-----------------------------------------" << std::endl;
    }
}