CC=g++
LEDAID='/usr/local/LEDA'
LEDAINCL='/usr/local/LEDA/incl'
CFLAGS= -I$(LEDAINCL) -L$(LEDAID) -O3 -lleda -std=c++0x -I'incl'
TARGET=bin/bdbfs


all:
	$(CC) main.cpp src/*.cpp -o $(TARGET) $(CFLAGS) 
	
info:
	$(CC) main.cpp src/*.cpp -o $(TARGET) $(CFLAGS) -D INFO=1

clean:
	rm bin/bdbfs
