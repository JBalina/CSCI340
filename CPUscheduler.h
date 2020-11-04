//Jonathan Balina CSCI340

#ifndef CPUscheduler_H_
#define CPUscheduler_H_

#include<iostream>
#include<list>
#include<vector>
#include<string>
#include"PCB.h"
#include"RAM.h"

class CPUscheduler
{
private:
	RAM memory;
	int page_size;
	std::list<PCB> ReadyQueue;
	std::vector<std::list<PCB>> IOqueue;
	std::list<PCB> terminated;
	std::list<PCB> zombies;
	std::list<PCB> wait;
	void terminate_children(PCB process);
public:
	CPUscheduler(long long rsize, long long psize, int IOsize);
	void addNewProcess(int nPID);
	void addNewChild(int nPID);
	void nextProcess();
	void terminate();
	void processWait();
	void requestIO(int num, std::string file_name);
	void IOprog(int num);
	void allocateMem(int pageNum, int tStamp);
	void print_Ready();
	void print_IO();
	void print_memory();
};


#endif
