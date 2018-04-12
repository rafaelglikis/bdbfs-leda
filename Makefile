LEDAID='/usr/local/LEDA'
LEDAINCL='/usr/local/LEDA/incl'

all:
	g++ main.cpp src/bfs.cpp src/bdbfs.cpp src/tests.cpp -o run -I$(LEDAINCL) -L$(LEDAID) -O3 -lleda -std=c++0x
	
info:
	g++ main.cpp src/bfs.cpp src/bdbfs.cpp src/tests.cpp -o run -I$(LEDAINCL) -L$(LEDAID) -O3 -lleda -std=c++0x -D INFO=1
