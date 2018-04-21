#include "bdbfs.h"

namespace bdbfs
{
    /**
     * Finds the shortest path by running my bdBFS implementation.
    */
    std::list<leda::edge> shortestPath(leda::graph& G, leda::node& source, leda::node& target)
    {
        std::list<leda::edge> path; // Contains every edge of shortest path from source to target
        
        // Shortest paths
        leda::node_array<leda::edge> pred(G); 
        leda::node_array<leda::edge> succ(G);

        leda::node middleNode = bdBFS(G, source, target, pred, succ);

        #ifdef INFO
        printInfo(G, pred, succ, source, target, middleNode);
        #endif

        // If middleNode not discovered then Graph is not strongly coherent
        if(middleNode == nil) {
            #ifdef INFO
            std::cout << "[i] Graph not strongly coherent." << std::endl;
            #endif
            return path;
        }

        // Add edges discovered by headSteps (pred)
        leda::node checkpoint = middleNode;
        while (checkpoint != source) {
            path.push_front(pred[checkpoint]);
            checkpoint = G.source(pred[checkpoint]);
        }
        // Add edges discovered by tailSteps (succ)
        checkpoint = middleNode;
        while (checkpoint != target) {
            path.push_back(succ[checkpoint]);
            checkpoint = G.target(succ[checkpoint]);
        }

        return path;
    }
    
    /**
     * my bdBFS implementation.
    */
    leda::node bdBFS(leda::graph& G, leda::node& source, leda::node& target, 
        leda::node_array<leda::edge>& pred, leda::node_array<leda::edge>& succ) 
    {
        // bdBFS queues
        std::deque<leda::node> bfsQueue;
        std::deque<leda::node> rbfsQueue;
        
        leda::node middleNode = nil;

        // First step
        bfsQueue.push_back(source);
        rbfsQueue.push_back(target);
        
        // In case we are lucky
        if(target == source) {
            return target;
        }    

        // Search until we find the middle node or queues are empty
        while (middleNode==nil && !bfsQueue.empty() && !rbfsQueue.empty()) {
            bfsStep(G, bfsQueue, pred, succ, middleNode);
            if(middleNode !=nil){
                break;
            } 
            rbfsStep(G, rbfsQueue, succ, pred, middleNode);
        } 

        return middleNode;
    }

    /**
     * Run step of bfs algorithm.
     * Discoveres one level of nodes.
    */
    void bfsStep(leda::graph& G, std::deque<leda::node>& bfsQueue, leda::node_array<leda::edge>& pred, leda::node_array<leda::edge>& succ, leda::node& middleNode)
    {
        leda::node v;
        leda::edge e;
        std::deque<leda::node> nodesQueue(bfsQueue); // Copies bfs queue (deallocated when out of scope)
        bfsQueue.clear();
        // Run until you discover next level of nodes.
        while (!nodesQueue.empty()) {
            v = nodesQueue.back(); 
            nodesQueue.pop_back();
            forall_out_edges(e,v) { 
                if(pred[G.target(e)]==nil) {
                    #ifdef INFO
                    std::cout << "bfs: "; G.print_edge(e); std::cout<<std::endl;
                    #endif
                    // push next level nodes to the original bfsQueue
                    bfsQueue.push_back(G.target(e));
                    // Add to pred array only if entry is empty
                    if(pred[G.target(e)]==nil && G.target(e)!=G.source(e)) {
                        pred[G.target(e)] = e; 
                    } 
                }
                
                // If you find middle node finish
                if(succ[G.target(e)]) {
                    middleNode = G.target(e);
                    return;
                }
            }
        }
    }

    /**
     * Run step of rbfs algorithm.
     * Discoveres one level of nodes.
    */
    void rbfsStep(leda::graph& G, std::deque<leda::node>& rbfsQueue, leda::node_array<leda::edge>& succ, leda::node_array<leda::edge>& pred, leda::node& middleNode)
    {
        leda::node t;
        leda::edge e;
        std::deque<leda::node> nodesQueue(rbfsQueue); // Copies rbfs queue (deallocated when out of scope)
        rbfsQueue.clear();
        // Run until you discover next level of nodes.
        while (!nodesQueue.empty()) {
            t = nodesQueue.back(); nodesQueue.pop_back();
            forall_in_edges(e,t) { 
                if(succ[G.source(e)]==nil) {
                    #ifdef INFO
                    std::cout << "rbfs: "; G.print_edge(e); std::cout<<std::endl;
                    #endif
                    // push next level nodes to the original rbfsQueue
                    rbfsQueue.push_back(G.source(e));
                    // Add to succ array only if entry is empty
                    if(succ[G.source(e)]==nil && G.target(e)!=G.source(e)) {
                        succ[G.source(e)] = e;
                    } 
                }
                
                // If you find middle node finish
                if(pred[G.source(e)]) {
                    middleNode = G.source(e);
                    return;
                }
            }  
        }
    }

    /**
     * Prints the result of the algorithm.
    */
    void printInfo(leda::graph& G, 
        leda::node_array<leda::edge>& pred, leda::node_array<leda::edge>& succ, 
        leda::node& source, leda::node& target, leda::node&  middleNode)
    {
        leda::node v;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "|\t B D B F S  I N F O\t\t|" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "| * Source:  ";
        G.print_node(source);
        std::cout << "\t\t\t|" << std::endl << "| * Target:  ";
        G.print_node(target);
        std::cout << "\t\t\t|" << std::endl << "| * Middle:  ";
        if (middleNode==nil) std::cout << "NIL";
        else G.print_node(middleNode);
        std::cout << "\t\t\t|" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "|node\t" << "|   pred  |   succ  |" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        forall_nodes(v,G) {
            std::cout << "| ";
            G.print_node(v);
            std::cout << "\t| ";
            if (pred[v]!=nil) { 
                G.print_edge(pred[v]); 
                std::cout << "\t";
            } else {
                std::cout << "\t\t";
            }
            std::cout << "| ";
            if (succ[v]!=nil) { 
                std::cout<< "*";
                G.print_edge(succ[v]);
            } else {
                std::cout << "\t";
            }
            std::cout << "\t|" << std::endl;
        }
        std::cout << "-----------------------------------------" << std::endl;
    }
}