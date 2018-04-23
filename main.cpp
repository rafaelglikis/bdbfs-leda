#include <iostream>
#include "tests.h"

int main(int argc, char** argv)
{
    // print usage
    if (argc != 2) {
        std::cout << "Usage: " << std::endl;
        std::cout << "\t" << argv[0] << " test-small (run small tests)" << std::endl; 
        std::cout << "\t" << argv[0] << " test-all (run all tests)" << std::endl; 
        std::cout << "\t" << argv[0] << " benchmark (run all benchmarks)" << std::endl; 
        return -1;
    }
    
    std::string command = argv[1];

    // Run small tests only
    if (!command.compare("test-small")){
        test::testNonCoherentGraph();
        test::testTinyGraph();
        test::testTinyGraph2();
        test::testTinyOddGraph();
    }

    // Run all tests
    if (!command.compare("test-all")){
        test::testNonCoherentGraph();
        test::testTinyGraph();
        test::testTinyGraph2();
        test::testTinyOddGraph();
        test::testRandomGraphs();
        test::testGridGraphs();
    }

    // Run benchmarks
    if (!command.compare("benchmark")){
        test::benchmarkRandomGraphs();
        test::benchmarkGridGraphs();
    }

    return 0;
}
