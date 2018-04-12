#include <iostream>
#include "incl/tests.h"

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: " << std::endl;
        std::cout << "\t" << argv[0] << " test (run all tests)" << std::endl; 
        std::cout << "\t" << argv[0] << " benchmark (run all benchmarks)" << std::endl; 
    }
    
    std::string command = argv[1];

    if (!command.compare("test")){
        test::testNonCoherentGraph();
        test::testTinyGraph();
        test::testTinyGraph2();
        test::testTinyOddGraph();
    }

    if (!command.compare("benchmark")){
        test::testRandomGraphs();
        test::testGridGraphs();
    }

    return 0;
}
