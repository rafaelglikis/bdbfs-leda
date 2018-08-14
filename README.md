# Bidirectional Breadth First Search using LEDA
Comparison of LEDA's BFS algorithm with bidirectional BFS.

## Requirements
* LEDA

## Compile
modify Makefile

	LEDAID='/usr/local/LEDA'
	LEDAINCL='/usr/local/LEDA/incl'

and then:
	
	make

## Usage
	
	./bin/bdbfs test-small (run small tests)
	./bin/bdbfs test-all (run all tests)
	./bin/bdbfs benchmark (run all benchmarks)

