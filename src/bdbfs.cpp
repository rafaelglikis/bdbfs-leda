#include "../incl/bdbfs.h"

namespace bdbfs
{
    std::list<leda::edge> shortestPath(leda::graph& G, leda::node& source, leda::node& target)
    {
        std::list<leda::edge> path; // Contains every edge of shortest path from source to target

        // Shortest paths
        leda::node_array<leda::edge> predSource(G); 
        leda::node_array<leda::edge> predTarget(G);

        leda::node middleNode = bdBFS(G, source, target, predSource, predTarget);

        #ifdef INFO
        printInfo(G, predSource, predTarget, source, middleNode, target);
        #endif

        // If middleNode not discovered then Graph is not strongly coherent
        if(middleNode == nil) {
            std::cout << "[i] Graph not strongly coherent." << std::endl;
            return path;
        }

        // Add edges discovered by headSteps
        leda::node checkpoint = middleNode;
        while (checkpoint != source) {
            if (predSource[checkpoint]!=nil) {   
                path.push_front(predSource[checkpoint]);
                checkpoint = G.source(predSource[checkpoint]);
            }
        }
        // if(middleNode == target) return path;

        // Add edges discovered by tailSteps
        checkpoint = middleNode;
        while (checkpoint != target) {
            if (predTarget[checkpoint]!=nil) {   
                path.push_back(predTarget[checkpoint]);
                checkpoint = G.target(predTarget[checkpoint]);
            }
        }

        return path;
    }
    
    leda::node bdBFS(leda::graph& G, leda::node& source, leda::node& target, 
        leda::node_array<leda::edge>& predSource, leda::node_array<leda::edge>& predTarget) 
    {
        // bdBFS queues
        std::deque<leda::node> sourceQ;
        std::deque<leda::node> targetQ;

        // Discocered Nodes
        leda::node_array<bool> sourceDiscoveredNodes(G, false);
        leda::node_array<bool> targetDiscoveredNodes(G, false);

        leda::node middleNode = nil;

        // First step
        sourceQ.push_back(source);
        sourceDiscoveredNodes[source] = true;
        targetQ.push_back(target);
        targetDiscoveredNodes[target] = true;    
        
        // In case we are lucky
        if(target == source) {
            return target;
        }    

        // Search until we find the middle node or queues are empty
        while (middleNode==nil && !sourceQ.empty() && !targetQ.empty()) {
            headStep(G, targetDiscoveredNodes, sourceDiscoveredNodes, 
                sourceQ, predSource, middleNode);

            if(middleNode !=nil) break;

            tailStep(G, targetDiscoveredNodes, sourceDiscoveredNodes, 
                targetQ, predTarget, middleNode);
        } 

        return middleNode;
    }

    void headStep(leda::graph& G, leda::node_array<bool>& targetDiscoveredNodes, leda::node_array<bool>& sourceDiscoveredNodes, 
        std::deque<leda::node>& sourceQ, leda::node_array<leda::edge>& predSource, leda::node& middleNode)
    {
        leda::node v;
        leda::edge e;
        std::deque<leda::node> tmpQ(sourceQ);
        sourceQ.clear();
        while (!tmpQ.empty()) {
            v = tmpQ.back(); tmpQ.pop_back();
            forall_out_edges(e,v) { 
                if(!sourceDiscoveredNodes[G.target(e)]) {
                    #ifdef INFO
                    std::cout << "S: "; G.print_edge(e); std::cout<<std::endl;
                    #endif
                    sourceDiscoveredNodes[G.target(e)] = true;
                    sourceQ.push_back(G.target(e));
                    if(predSource[G.target(e)]==nil && G.target(e)!=G.source(e)) {
                        predSource[G.target(e)] = e; 
                    } 
                }
                if(targetDiscoveredNodes[G.target(e)]) {
                    middleNode = G.target(e);
                    return;
                }
            }
        }
    }

    void tailStep(leda::graph& G, leda::node_array<bool>& targetDiscoveredNodes, leda::node_array<bool>& sourceDiscoveredNodes, 
        std::deque<leda::node>& targetQ, leda::node_array<leda::edge>& predTarget, leda::node& middleNode)
    {
        leda::node t;
        leda::edge e;
        std::deque<leda::node> tmpQ(targetQ);
        targetQ.clear();
        while (!tmpQ.empty()) {
            t = tmpQ.back(); tmpQ.pop_back();
            forall_in_edges(e,t) { 
                if(!targetDiscoveredNodes[G.source(e)]) {
                    #ifdef INFO
                    std::cout << "T: "; G.print_edge(e); std::cout<<std::endl;
                    #endif
                    targetDiscoveredNodes[G.source(e)] = true;
                    targetQ.push_back(G.source(e));
                    if(predTarget[G.source(e)]==nil && G.target(e)!=G.source(e)) {
                        predTarget[G.source(e)] = e;
                    } 
                }
                if(sourceDiscoveredNodes[G.source(e)]) {
                    middleNode = G.source(e);
                    return;
                }
            }  
        }
    }

    void printInfo(leda::graph& G, 
        leda::node_array<leda::edge>& predSource, leda::node_array<leda::edge>& predTarget, 
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
        G.print_node(middleNode);
        std::cout << "\t\t\t|" << std::endl;
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
    }
}