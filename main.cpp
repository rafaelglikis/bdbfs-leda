#include <iostream>
#include "incl/tests.h"

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: " << std::endl;
        std::cout << "\t" << argv[0] << " tests (run all tests)" << std::endl; 
    }
    
    std::string command = argv[1];

    if (!command.compare("tests")){
        testTinyGraph();
        testRandomGraphs();
        //testGridGraphs();
    }

    return 0;
}
