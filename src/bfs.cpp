#include "../incl/bfs.h"
#define INFO 1

std::list<leda::edge> ledaShortestPathBFS(leda::graph &G, leda::node &source, leda::node &target) 
{
    // Running BFS
    leda::node_array<int> dist(G,-1); // The distance from source to nodes v in G
    leda::node_array<leda::edge> pred(G); // Pred contains the edge that was used by BFS to reach v or nil, for every node v of G.
    BFS(G,source,dist,pred);
    
    leda::node v;
    #ifdef INFO
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "|\t L E D A  B F S \t\t|" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "|node\t" << "|    distance\t" << "| shortest-path |" << std::endl;
        forall_nodes(v,G) {
            std::cout << "| ";
            G.print_node(v);
            std::cout << "\t|\t" << dist[v] << "\t| ";
            if (pred[v]!=nil) G.print_edge(pred[v]);
            else std::cout << "\t";
            std::cout << "\t|" << std::endl;
        }
        std::cout << "-----------------------------------------" << std::endl;
    #endif

    // Finding Shortest Path
    std::list<leda::edge> path; // Contains every edge of shortest path from source to target
    leda::node checkpoint = target;
    while (checkpoint != source) {
        forall_rev_nodes(v,G) {
            if (pred[v]!=nil && G.target(pred[v]) == checkpoint) {   
                checkpoint = G.source(pred[v]);
                path.push_front(pred[v]);
            }
        }
    }

    #ifdef INFO
    std::cout << "Shortest path: " << std::endl;
    for (std::list<leda::edge>::iterator it = path.begin(); it != path.end(); ++it) {
        G.print_edge(*it);
        std::cout << std::endl;
    }   
    #endif
    return path;
}

std::list<leda::edge> bdBFS(leda::graph &G, leda::node &source, leda::node &target) 
{
    std::deque<leda::node> sourceQ;
    std::deque<leda::node> targetQ;
    std::unordered_set<leda::node> sourceDiscoveredNodes;
    std::unordered_set<leda::node> targetDiscoveredNodes;
    
    leda::node_array<leda::edge> pred(G); // Pred contains the edge that was used by BFS to reach v or nil, for every node v of G.
    
    leda::node v;
    leda::node t;

    sourceQ.push_back(source);
    targetQ.push_back(target);
    sourceDiscoveredNodes.insert(v);
    targetDiscoveredNodes.insert(t);
    
    leda::edge e;  
    while (!sourceQ.empty() && !targetQ.empty()) {
        v = sourceQ.back(); sourceQ.pop_back();
        t = targetQ.back(); targetQ.pop_back();

        forall_out_edges(e,v) { 
            if(sourceDiscoveredNodes.insert(G.target(e)).second){
                sourceQ.push_back(G.target(e));
                if(pred[G.target(e)]==nil && G.target(e)!=G.source(e)) pred[G.target(e)] = e; 
            }
            if(targetDiscoveredNodes.find(G.target(e)) != targetDiscoveredNodes.end()) goto endloop;
        }
        
        forall_in_edges(e,t) { 
            if(targetDiscoveredNodes.insert(G.source(e)).second) {
                targetQ.push_back(G.source(e));
                if(pred[G.target(e)]==nil && G.target(e)!=G.source(e)) pred[G.target(e)] = e; 
            }
            if(sourceDiscoveredNodes.find(G.source(e)) != targetDiscoveredNodes.end()) goto endloop;
        }       
    } 
    
    endloop:

    #ifdef INFO
        std::cout << "Source: ";
        G.print_node(source);
        std::cout << std::endl << "Target";
        G.print_node(target);
        std::cout << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << "|     R A F A B F S     |" << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << "|node\t" << "| shortest-path |" << std::endl;
        forall_nodes(v,G) {
            std::cout << "| ";
            G.print_node(v);
            std::cout << "\t| ";
            if (pred[v]!=nil) G.print_edge(pred[v]);
            else std::cout << "\t";
            std::cout << "\t|" << std::endl;
        }
        std::cout << "-------------------------" << std::endl;
    #endif
    
    std::list<leda::edge> path; // Contains every edge of shortest path from source to target
    
    leda::node checkpoint = target;
    while (checkpoint != source) {
        forall_rev_nodes(v,G) {
            if (pred[v]!=nil && G.target(pred[v]) == checkpoint) {   
                checkpoint = G.source(pred[v]); 
                path.push_front(pred[v]);
            }
        }
        //break;
    }

    #ifdef INFO
    std::cout << "Shortest path: " << std::endl;
    for (std::list<leda::edge>::iterator it = path.begin(); it != path.end(); ++it) {
        G.print_edge(*it);
        std::cout << std::endl;
    }   
    #endif

    return path;
}

