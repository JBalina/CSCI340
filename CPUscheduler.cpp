//Jonathan Balina CSCI340
#include"CPUscheduler.h"
#include"PCB.h"

CPUscheduler::CPUscheduler(long long rsize, long long psize, int IOsize)
{
	memory = RAM(rsize, psize);
	for(int i = 0; i < IOsize; i++)
	{
		std::list<PCB> temp;
		IOqueue.push_back(temp);
	}
}

void CPUscheduler::addNewProcess(int nPID)
{
	PCB nProcess(nPID);
	if(ReadyQueue.empty())
	{
		nProcess.state = RUNNING;
		ReadyQueue.push_front(nProcess);
	}
	else
	{
		nProcess.state = READY;
		ReadyQueue.push_back(nProcess);
	}
}

void CPUscheduler::addNewChild(int nPID)
{
	addNewProcess(nPID);
	ReadyQueue.front().childrenPID.push_back(nPID);
	ReadyQueue.back().hasParent = true;
	ReadyQueue.back().parentPID = ReadyQueue.front().PID;
}

void CPUscheduler::nextProcess()
{
	ReadyQueue.splice(ReadyQueue.end(), ReadyQueue, ReadyQueue.begin());
	ReadyQueue.front().state = RUNNING;
	ReadyQueue.back().state = READY;
}

void CPUscheduler::terminate_children(PCB process)
{
	for(int i = 0; i < process.childrenPID.size(); i++)
	{
		for(auto j : ReadyQueue)
		{
			if(j == process.childrenPID[i])
			{
				terminate_children(j);
				memory.deallocate(j.PID);
				terminated.push_back(j);
				ReadyQueue.remove(j);
				break;
			}
		}
		for(auto j : wait)
		{
			if(j == process.childrenPID[i])
			{
				terminate_children(j);
				memory.deallocate(j.PID);
				terminated.push_back(j);
				wait.remove(j);
				break;
			}
		}
		for(auto j : zombies)
		{
			if(j == process.childrenPID[i])
			{
				terminate_children(j);
				memory.deallocate(j.PID);
				terminated.push_back(j);
				zombies.remove(j);
				break;
			}
		}
		for(int j = 0; j < IOqueue.size(); j++)
		{
			//std::vector<PCB> temp;
			for(auto k : IOqueue[j])
			{
				if(k == process.childrenPID[i])
				{
					terminate_children(k);
					memory.deallocate(k.PID);
					terminated.push_back(k);
					//temp.push_back(k);
					IOqueue[j].remove(k);
					break;
				}
			}
			/*for(auto k : temp)
			{
				IOqueue[j].remove(k);
			}*/
		}
		//Remove this comment once you handle the PCBs in wait and zombies
	}
}

void CPUscheduler::terminate()
{
	terminate_children(ReadyQueue.front());
	memory.deallocate(ReadyQueue.front().PID);
	if(ReadyQueue.front().hasParent)
	{
		bool waitingParent = false;
		for(auto i : wait)
		{
			if(i == ReadyQueue.front().parentPID)
			{
				waitingParent = true;
				ReadyQueue.push_back(i);
				ReadyQueue.back().state == READY;
				wait.remove(i);
				break;
			}
		}
		if(waitingParent)
		{
			terminated.push_back(ReadyQueue.front());
		}
		else
			zombies.push_back(ReadyQueue.front());
		
	}
	ReadyQueue.pop_front();
	ReadyQueue.front().state = RUNNING;
}

void CPUscheduler::processWait()
{
	bool hasZombie = false;
	for(int i = 0; i < ReadyQueue.front().childrenPID.size(); i++)
	{	
		for(auto j : zombies)
		{
			if(j == ReadyQueue.front().childrenPID[i])
			{
				hasZombie = true;
				terminated.push_back(j);
				zombies.remove(j);
				
				break;
			}
		}
		if(hasZombie)
			break;
	}
	if(hasZombie)
		return;
	else
	{
		wait.push_back(ReadyQueue.front());
		ReadyQueue.pop_front();
		ReadyQueue.front().state = RUNNING;
	}
}

void CPUscheduler::requestIO(int num, std::string file_name)
{
	IOqueue[num].push_back(ReadyQueue.front());
	IOqueue[num].back().state = WAITING;
	IOqueue[num].back().file = file_name;
	ReadyQueue.pop_front();
	ReadyQueue.front().state = RUNNING;
}

void CPUscheduler::IOprog(int num)
{
	ReadyQueue.push_back(IOqueue[num].front());
	ReadyQueue.back().state = READY;
	IOqueue[num].pop_front();
}

void CPUscheduler::allocateMem(int pageNum, int tStamp)
{
	memory.allocate(ReadyQueue.front().PID, pageNum, tStamp);
}

void CPUscheduler::print_Ready()
{
	if(ReadyQueue.empty())
	{
		std::cout << "There is no process using CPU." << std::endl;
		return;
	}
	int i = 0;
	for(auto j : ReadyQueue)
	{
		if(i == 0)
		{
			std::cout << "Currently running process:" << std::endl;
			std::cout << "\tProcess #" << j.PID << std::endl;
			if(ReadyQueue.size() > 1)
				std::cout << "Processes in ready-queue:" << std::endl;
		}
		else
		{
			std::cout << "\tProcess #" << j.PID << std::endl;
		}
		i++;
	}
}

void CPUscheduler::print_IO()
{
	for(int i = 0; i < IOqueue.size(); i++)
	{
		if(!(IOqueue[i].empty()))
		{
			int notfirst = 0;
			std::cout << "Process currently using hard disk #" << i << ":" << std::endl;
			for(auto j : IOqueue[i])
			{
				if(notfirst == 1)
					std::cout << "Processes waiting for hard disk #" << i << ":" << std::endl;
				std::cout << "\tProcess #" << j.PID << "\t" << j.file << std::endl;
				notfirst++;
			}
		}
		else if(IOqueue[i].empty())
		{
			std::cout << "There are no processes waiting for hard disk #" << i << std::endl;
		}
	}
}

void CPUscheduler::print_memory()
{
	memory.print();
}



