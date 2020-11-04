#Jonathan Balina
CXX       := /usr/bin/g++
CXXFLAGS  += -W -g
CXXFLAGS  += -std=c++0x 

all: Proj

.PHONY: clean  cleanall
clean:
	rm -f *.o

cleanall:
	rm -f *.o Proj
	
Proj: main.cpp CPUscheduler.cpp CPUscheduler.h PCB.cpp PCB.h RAM.cpp RAM.h
	$(CXX) $(CXXFLAGS) main.cpp CPUscheduler.cpp PCB.cpp RAM.cpp -o Proj

