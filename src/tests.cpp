#include "../incl/tests.h"
#define INFO 1

bool testTinyGraph()
{    
    #ifdef INFO
        std::cout << "[i] Testing tiny graph." << std::endl; 
    #endif

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
    
    test(G, n1, n9);   
}

// http://graphics.stanford.edu/courses/cs368-00-spring/TA/manuals/LEDA/graph_gen.html
bool testRandomGraphs()
{
    int nodesCount[] = {10, 100, 1000, 10000};
    //nodesCount[2] = 100000; // NOT ENOUGH MEMORY

    for(short i = 0; i<sizeof(nodesCount)/sizeof(nodesCount[0]); ++i)
    {

        std::cout << "[i] Testing random graph with " << nodesCount[i] 
            << " nodes and " << 4*nodesCount[i] <<  " edges." << std::endl; 

        leda::graph G;
        leda::random_graph(G,nodesCount[i], 4*nodesCount[i]); 
        Make_Connected(G);
        leda::node source = G.choose_node();
        leda::node target = G.choose_node();
        test(G, source, target);

        if(i==1) break; // NOT ENOUGH MEMORY

        std::cout << "[i] Testing random graph with " << nodesCount[i] 
            << " nodes and " << round(nodesCount[i]*log(nodesCount[i])) <<  " edges." << std::endl; 
        leda::graph GG;
        leda::random_graph(GG,nodesCount[i],round(nodesCount[i]*log(nodesCount[i]))); 
        Make_Connected(GG);
        source = GG.choose_node();
        target = GG.choose_node();
        test(GG, source, target);
    }
}

bool testGridGraphs()
{
    int height = 100;
    int width[] = {1000, 10000};
    
    for(short i = 0; i<sizeof(width)/sizeof(width[0]); ++i)
    {

        std::cout << "[i] Testing grid graph with " << height 
            << " nodes and " << width[i] <<  " edges." << std::endl; 

        leda::graph G;
        leda::node_array<double> xcoord;
        leda::node_array<double> ycoord;
        leda::grid_graph(G, xcoord, ycoord, height); // width?

        leda::node source = G.choose_node();
        leda::node target = G.choose_node();
        test(G, source, target);
    }
}

bool test(leda::graph& G, leda::node& source, leda::node& target)
{
    std::list<leda::edge> path = ledaShortestPathBFS(G, source, target);
    std::list<leda::edge> mpath = bdBFS(G, source, target);

    std::list<leda::edge>::iterator it1 = path.begin();
    std::list<leda::edge>::iterator it2 = mpath.begin();

    // Testing size
    if(path.size() != mpath.size()) {
        std::cout << "[-] Test failed: " << std::endl;
        std::cout << "    expected size: " << path.size() << std::endl; 
        std::cout << "    actual size: " << mpath.size() << std::endl; 
        return false;
    }

    while( it1 != path.end() && it2 != mpath.end()) {
        if(*it1 != *it2) {
            std::cout << "[-] Test failed: " << std::endl;
            std::cout << "    expected: "; 
            G.print_edge(*it1);
            std::cout << std::endl;
            std::cout << "    actual: "; 
            G.print_edge(*it2);
            std::cout << std::endl;
            return false;
        }

        it1++;
        it2++;    
    }

    std::cout << "[+] Test Pass!" << std::endl;
    return true;
}