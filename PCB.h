//Jonathan Balina CSCI340

#ifndef PCB_H_
#define PCB_H_
#include<vector>
#include<string>

enum states {NEW, RUNNING, WAITING, READY, TERMINATED};

struct PCB
{
//private:
	states state;
	int PID;
	bool isZombie;
	std::vector<int> childrenPID;
	bool hasParent;
	int parentPID;		
	std::string file;
//public:
	PCB();
	PCB(int nPID);
	bool operator==(int match_PID);
	bool operator==(PCB match_PCB);
};

#endif
