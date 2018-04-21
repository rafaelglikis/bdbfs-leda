#ifndef TESTS_H
#define TESTS_H

#include "../incl/bfs.h"
#include "../incl/bdbfs.h"
#include "../incl/graph_helper.h"
#include <vector>
#include <utility>

#include <ctime>

namespace test 
{
    bool testTinyGraph();
    bool testTinyGraph2();
    bool testTinyOddGraph();
    bool testNonCoherentGraph();
    bool testRandomGraphs();
    bool testGridGraphs();
    bool test(leda::graph&, leda::node&, leda::node&, std::string);
}

#endif