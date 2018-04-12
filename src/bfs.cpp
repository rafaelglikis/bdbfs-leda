#include "../incl/bfs.h"

std::list<leda::edge> shortestPathBFS(leda::graph &G, leda::node &source, leda::node &target) 
{
    // Running BFS
    leda::node_array<int> dist(G,-1); // The distance from source to nodes v in G
    leda::node_array<leda::edge> pred(G); // Pred contains the edge that was used by BFS to reach v or nil, for every node v of G.
    BFS(G,source,dist,pred);
    
    leda::node v;
    #ifdef INFO
    std::cout << "Source: ";
    G.print_node(source);
    std::cout << std::endl << "Target: ";
    G.print_node(target);
    std::cout << std::endl;
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

    return shortestPath(G, source, target, pred);
}



std::list<leda::edge> bdBFS(leda::graph &G, leda::node &source, leda::node &target) 
{
    std::deque<leda::node> sourceQ;
    std::deque<leda::node> targetQ;
    leda::node_array<bool> sourceDiscoveredNodes(G, false);
    leda::node_array<bool> targetDiscoveredNodes(G, false);
    
    leda::node_array<leda::edge> predSource(G); 
    leda::node_array<leda::edge> predTarget(G); 
    
    leda::node v;
    leda::node t;

    sourceQ.push_back(source);
    targetQ.push_back(target);
    sourceDiscoveredNodes[source] = true;
    targetDiscoveredNodes[target] = true;    

    leda::node middleNode = nil;


    std::list<leda::edge> path; // Contains every edge of shortest path from source to target
    if(target == source) {
        return path;
    } else if(targetDiscoveredNodes[source]) {
        middleNode = source;
    } else if(sourceDiscoveredNodes[target]) {
        middleNode = target;
    }

    leda::edge e;
    while (!sourceQ.empty() && !targetQ.empty() && middleNode==nil) {
        // BFS step from the start node
        std::deque<leda::node> *tmpQ = new std::deque<leda::node>(sourceQ);
        sourceQ.clear();
        while (!tmpQ->empty() && middleNode==nil) {
            v = tmpQ->back(); 
            tmpQ->pop_back();
            forall_out_edges(e,v) { 
                if(!sourceDiscoveredNodes[G.target(e)]) {
                    #ifdef INFO
                    std::cout << "S: ";
                    G.print_edge(e);
                    std::cout<<std::endl;
                    #endif
                    sourceDiscoveredNodes[G.target(e)] = true;
                    sourceQ.push_back(G.target(e));
                    if(predSource[G.target(e)]==nil && G.target(e)!=G.source(e)) {
                        predSource[G.target(e)] = e; 
                    } 
                }
                if(targetDiscoveredNodes[G.target(e)]) {
                    middleNode = G.target(e);
                    break;
                }
            }
        }
        delete tmpQ;

        if(middleNode !=nil) break;

        // BFS step from the finish node
        tmpQ = new std::deque<leda::node>(targetQ);
        targetQ.clear();
        while (!tmpQ->empty() && middleNode==nil) {
            t = tmpQ->back(); tmpQ->pop_back();
            forall_in_edges(e,t) { 
                if(!targetDiscoveredNodes[G.source(e)]) {
                    #ifdef INFO
                    std::cout << "T: ";
                    G.print_edge(e);std::cout<<std::endl;
                    #endif
                    targetDiscoveredNodes[G.source(e)] = true;
                    targetQ.push_back(G.source(e));
                    if(predTarget[G.source(e)]==nil && G.target(e)!=G.source(e)) {
                        predTarget[G.source(e)] = e;
                    } 
                }
                if(sourceDiscoveredNodes[G.source(e)]) {
                    middleNode = G.source(e);
                    break;
                }
            }  
        }
        delete tmpQ;
    } 

    // Finding Shortest Path
    if(middleNode == nil) {
        std::cout << "[i] Graph not strongly coherent." << std::endl;
        return path;
    }

    #ifdef INFO
    //leda::node v;
    std::cout << " * Source: ";
    G.print_node(source);
    std::cout << std::endl << " * Target: ";
    G.print_node(target);
    std::cout << std::endl << " * Middle: ";
    G.print_node(middleNode);
    std::cout << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "|node\t" << "|   predSource  |   predTarget  |" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    forall_nodes(v,G) {
        std::cout << "| ";
        G.print_node(v);
        std::cout << "\t| ";
        if (predSource[v]!=nil) { 
            G.print_edge(predSource[v]); 
            std::cout << "\t";
        } else {
            std::cout << "\t\t";
        }
        std::cout << "| ";
        if (predTarget[v]!=nil) { 
            std::cout<< "*";
            G.print_edge(predTarget[v]);
        } else {
            std::cout << "\t";
        }
        std::cout << "\t|" << std::endl;
    }
    std::cout << "-----------------------------------------" << std::endl;
    #endif

    leda::node checkpoint = middleNode;
    while (checkpoint != source) {
        if (predSource[checkpoint]!=nil) {   
            path.push_front(predSource[checkpoint]);
            checkpoint = G.source(predSource[checkpoint]);
        }
    }
    
    if(middleNode == target) {
        return path;
    }

    checkpoint = middleNode;
    while (checkpoint != target) {
        if (predTarget[checkpoint]!=nil) {   
            path.push_back(predTarget[checkpoint]);
            checkpoint = G.target(predTarget[checkpoint]);
        }
    }

    #ifdef INFO
    std::cout << "Shortest path (bdfs): " << std::endl;
    for (std::list<leda::edge>::iterator it = path.begin(); it != path.end(); ++it) {
        G.print_edge(*it);
        std::cout << std::endl;
    }   
    #endif
    
    return path;

}


std::list<leda::edge> shortestPath(leda::graph &G, leda::node &source, leda::node &target, leda::node_array<leda::edge> &pred)
{
    // Finding Shortest Path
    bool stop = true;
    leda::node v;
    std::list<leda::edge> path; // Contains every edge of shortest path from source to target
    leda::node checkpoint = target;

    
    if (pred[target]==nil) {
        std::cout << "[i] Graph not strongly coherent." << std::endl;
        return path;
    }
    
    while (checkpoint != source) {
        if (pred[checkpoint]!=nil) {   
            path.push_front(pred[checkpoint]);
            checkpoint = G.source(pred[checkpoint]);
        }
    }

    #ifdef INFO
    std::cout << "Shortest path (bfs): " << std::endl;
    for (std::list<leda::edge>::iterator it = path.begin(); it != path.end(); ++it) {
        G.print_edge(*it);
        std::cout << std::endl;
    }   
    #endif
    
    return path;
}