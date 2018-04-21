#ifndef TESTS_H
#define TESTS_H

#include "bfs.h"
#include "bdbfs.h"
#include "graph_helper.h"
#include <vector>
#include <utility>

#include <ctime>

namespace test 
{
    // Tests
    void test(leda::graph&, leda::node&, leda::node&, std::string);
    void testTinyGraph();
    void testTinyGraph2();
    void testTinyOddGraph();
    void testNonCoherentGraph();
    void testRandomGraphs();
    void testGridGraphs();

    // benchmarks
    void benchmark(leda::graph&, leda::node&, leda::node&, std::string);
    void benchmarkRandomGraphs();
    void benchmarkGridGraphs();
}

#define RUN_TIMES 20

#endif