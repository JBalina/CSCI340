//Jonathan Balina

#include"RAM.h"

RAM::page::page()
{
	used = false;
}

RAM::RAM()
{
}

RAM::RAM(long long Rsize, long long Psize)
{
	long long pseudoCapacity = (Rsize/Psize);
	page empty;
	empty.used = false;
	for(int i = 0; i < pseudoCapacity; i++)
	{
		frames.push_back(empty);
	}
}

void RAM::allocate(int proc, int pageN, int time)
{
	int i = 0;
	while((i != frames.size()) && (frames[i].used))
	{
		i++;
	}
	if(i == frames.size())
	{/* deallocate least recently used page */
		int n = 0;
		for(int j = 0; j < frames.size(); j++)
		{
			if(frames[j].timeStamp < frames[n].timeStamp)
			{
				n = j;
			}
		}
		frames[n].PID = proc;
		frames[n].pageNumber = pageN;
		frames[n].timeStamp = time;
	}
	else
	{
		frames[i].used = true;
		frames[i].PID = proc;
		frames[i].pageNumber = pageN;
		frames[i].timeStamp = time;
	}
}

void RAM::deallocate(int proc)
{
	for(int i = 0; i < frames.size(); i++)
	{
		if((frames[i].used) && (frames[i].PID == proc))
		{
			frames[i].used = false;
		}
	}
}

bool RAM::hasPage(int pageN)
{
	for(int i = 0; i < frames.size(); i++)
	{
		if((frames[i].used) && (frames[i].pageNumber == pageN))
		{
			return true;
		}
	}
	return false;
}

void RAM::print()
{
	bool empty = true;
	for(int i = 0; i < frames.size(); i++)
	{
		if(frames[i].used)
		{
			empty = false;
			std::cout << "Frame #" << i << std::endl;
			std::cout << "\tProcess #" << frames[i].PID << std::endl;
			std::cout << "\tPage #" << frames[i].pageNumber << std::endl;
		}
	}
	if(empty)
		std::cout << "No RAM memory is being used." << std::endl;
}
