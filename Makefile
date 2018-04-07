LEDAID='/usr/local/LEDA'
LEDAINCL='/usr/local/LEDA/incl'

all:
	g++ main.cpp src/bfs.cpp src/tests.cpp -o run -I$(LEDAINCL) -L$(LEDAID) -O3 -lleda -std=c++0x
