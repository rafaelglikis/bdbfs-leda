#include "../incl/tests.h"

namespace test 
{
    bool testTinyGraph()
    {    
        // Creating graph
        leda::graph G; 

        // Creating nodes
        leda::node n0=G.new_node();
        leda::node n1=G.new_node();
        leda::node n2=G.new_node();
        leda::node n3=G.new_node();
        leda::node n4=G.new_node();
        leda::node n5=G.new_node();
        leda::node n6=G.new_node();
        leda::node n7=G.new_node();
        leda::node n8=G.new_node();
        leda::node n9=G.new_node();
        leda::node n10=G.new_node();

        // Creating edges
        leda::edge e = G.new_edge(n1,n0);
        G.new_edge(n1,n2);
        G.new_edge(n1,n10);
        G.new_edge(n2,n3);
        G.new_edge(n3,n4);
        G.new_edge(n4,n5);
        G.new_edge(n5,n6);
        G.new_edge(n5,n7);
        G.new_edge(n6,n7);
        G.new_edge(n7,n8);
        G.new_edge(n7,n9);
        G.new_edge(n8,n9);
        G.new_edge(n10,n5);
        
        test(G, n1, n9, "tiny graph");   
    }

    bool testTinyGraph2()
    {    
        // Creating graph
        leda::graph G; 

        // Creating nodes
        leda::node n0=G.new_node();
        leda::node n1=G.new_node();
        leda::node n2=G.new_node();
        leda::node n3=G.new_node();
        leda::node n4=G.new_node();
        leda::node n5=G.new_node();
        leda::node n6=G.new_node();
        leda::node n7=G.new_node();
        leda::node n8=G.new_node();
        leda::node n9=G.new_node();
        leda::node n10=G.new_node();

        // Creating edges
        G.new_edge(n1,n8);
        G.new_edge(n3,n9);
        G.new_edge(n4,n9);
        G.new_edge(n6,n1);
        G.new_edge(n7,n4);
        G.new_edge(n8,n3);
        G.new_edge(n8,n7);
        G.new_edge(n8,n5);
        
        test(G, n6, n9, "complex path test");   
    }

    bool testTinyOddGraph()
    {    
        // Creating graph
        leda::graph G; 

        // Creating nodes
        leda::node n0=G.new_node();
        leda::node n1=G.new_node();
        leda::node n2=G.new_node();
        leda::node n3=G.new_node();
        leda::node n4=G.new_node();
        leda::node n5=G.new_node();
        leda::node n6=G.new_node();
        leda::node n7=G.new_node();
        leda::node n8=G.new_node();
        leda::node n9=G.new_node();
        leda::node n10=G.new_node();

        // Creating edges
        G.new_edge(n1,n8);
        G.new_edge(n3,n9);
        G.new_edge(n4,n9);
        G.new_edge(n6,n1);
        G.new_edge(n7,n4);
        G.new_edge(n8,n3);
        G.new_edge(n8,n7);
        G.new_edge(n8,n5);
        
        G.new_edge(n9,n10);
        
        test(G, n6, n10, "Odd Graph");   
    }

    bool testNonCoherentGraph()
    {    

        // Creating graph
        leda::graph G; 

        // Creating nodes
        leda::node n0=G.new_node();
        leda::node n1=G.new_node();
        leda::node n2=G.new_node();
        leda::node n3=G.new_node();
        leda::node n4=G.new_node();
        leda::node n5=G.new_node();
        leda::node n6=G.new_node();
        leda::node n7=G.new_node();
        leda::node n8=G.new_node();
        leda::node n9=G.new_node();
        leda::node n10=G.new_node();

        // Creating edges
        leda::edge e = G.new_edge(n1,n0);
        G.new_edge(n1,n2);
        G.new_edge(n1,n10);
        G.new_edge(n2,n3);
        G.new_edge(n3,n4);
        G.new_edge(n6,n7);
        G.new_edge(n7,n8);
        G.new_edge(n7,n9);
        G.new_edge(n8,n9);
        G.new_edge(n10,n5);
        
        return test(G, n1, n9, "Non Coherent");   
    }

    bool testRandomGraphs()
    {
        std::vector<std::pair<int,int>> graphSizes;
        graphSizes.push_back(std::make_pair(1000, 4*1000));
        graphSizes.push_back(std::make_pair(1000, 1000*log(1000)));
        graphSizes.push_back(std::make_pair(10000, 4*10000));
        graphSizes.push_back(std::make_pair(10000, 10000*log(10000)));
        graphSizes.push_back(std::make_pair(100000, 4*100000));
        graphSizes.push_back(std::make_pair(100000, 100000*log(100000)));
        
        for(std::vector<std::pair<int,int>>::iterator it = graphSizes.begin(); it!=graphSizes.end(); ++it)
        {
            leda::graph G;
            leda::random_graph(G, it->first, it->second); 
            Make_Connected(G);
            leda::node source = G.choose_node();
            leda::node target = G.choose_node();


            std::stringstream infostream;
            infostream << "Random graph with " << it->first << " nodes and " << it->second<<" edges.";
        
            test(G, source, target, infostream.str());
        }
    }

    #include <fstream>

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
    bool testGridGraphs()
    {
        
        int height = 100;
        int width[2]; 
        width[0] = 1000;
        width[1] = 10000;
        // width[2] = 100000; /// NOT ENOUGH MEMORY
        
        for(short i = 0; i<sizeof(width)/sizeof(width[0]); ++i)
        {
            std::stringstream infostream;
            infostream << "Grid graph " << height << "x" <<  width[i];
            leda::graph G = gridGraphCreator(height, width[i]);
            leda::node source = G.first_node();
            leda::node target = G.last_node();
            test(G, source, target, infostream.str());
        }

        
    }

    bool test(leda::graph& G, leda::node& source, leda::node& target, std::string info)
    {
        clock_t begin = clock();
        std::list<leda::edge> path = bfs::shortestPath(G, source, target);
        double elapsed_secs_leda = double(clock() - begin) / CLOCKS_PER_MS;

        #ifdef INFO
        std::cout << "Shortest path (bdfs): " << std::endl;
        for (std::list<leda::edge>::iterator it = path.begin(); it != path.end(); ++it) {
            G.print_edge(*it);
            std::cout << std::endl;
        }   
        #endif

        begin = clock();
        std::list<leda::edge> mpath = bdbfs::shortestPath(G, source, target);
        double elapsed_secs_rafa = double(clock() - begin) / CLOCKS_PER_MS;

        #ifdef INFO
        std::cout << "Shortest path (bdfs): " << std::endl;
        for (std::list<leda::edge>::iterator it = path.begin(); it != path.end(); ++it) {
            G.print_edge(*it);
            std::cout << std::endl;
        }   
        #endif
    

        std::list<leda::edge>::iterator it1 = path.begin();
        std::list<leda::edge>::iterator it2 = mpath.begin();

        // Testing size
        if(path.size() != mpath.size()) {
            std::cout << "[-] Test failed: " << std::endl;
            std::cout << "    expected size: " << path.size() << std::endl; 
            std::cout << "    actual size: " << mpath.size() << std::endl; 

            #ifdef INFO
            leda::edge e;
            forall_edges(e,G) {
                G.print_edge(e); 
                std::cout<<endl;
            }
            #endif

            return false;
        }

        std::cout << "[+] Test OK! (" << info << " ";
        G.print_node(source);
        std::cout << "->";
        G.print_node(target);
        std::cout << ")" << std::endl;
        std::cout << "    Time elapsed (leda): " << elapsed_secs_leda << " ms" << std::endl;
        std::cout << "    Time elapsed (rafa): " << elapsed_secs_rafa << " ms" << std::endl;

        return true;
    }
}
