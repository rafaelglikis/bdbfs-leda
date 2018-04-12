#ifndef TESTS_H
#define TESTS_H

#include "../incl/bfs.h"
#include "../incl/bdbfs.h"
#include <vector>
#include <utility>

#include <ctime>
#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)

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