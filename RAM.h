//Jonathan Balina

#ifndef RAM_H_
#define RAM_H_

#include<iostream>
#include<vector>
#include<list>
#include"PCB.h"

class RAM
{
private:
	struct page
	{
		bool used;
		int PID;
		int pageNumber;
		int timeStamp;
		page();
	};
	int page_size;
	int RAM_size;
	std::vector<page> frames;
public:
	RAM();
	RAM(long long Rsize, long long Psize);
	void allocate(int proc, int pageN, int time);
	void deallocate(int proc);
	bool hasPage(int pageN);
	void print();
};

#endif
