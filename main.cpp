/*Jonathan Balina
CSCI340
Pavel Shostak*/

#include<iostream>
#include<string>
#include<vector>
#include"CPUscheduler.h"
#include"PCB.h"
#include"RAM.h"

using namespace std;

int main()
{
	long long RAM_size, frame_size;
	int  num_hard_disks;
	cout << "How much RAM memory is there on the simulated computer?" << endl;
	cin >> RAM_size;
	cout << "What is the size of a frame?" << endl;
	cin >> frame_size;
	cout << "How many hard disks does the simulated computer have?" << endl;
	cin >> num_hard_disks;

	CPUscheduler myOS(RAM_size, frame_size, num_hard_disks);

	string input;
	int PID = 2;
	int time = 0;
	while(getline(cin,input))
	{
		input.erase(input.find_last_not_of("\n\r") + 1);
		cout << input << endl;
		/* ‘A’ input means that a new process has been created. When a new process arrives,
		 * your program should create its PCB and place the process in the end of the ready-queue.
		 * Initially, no memory is allocated for the new process. When choosing a PID for
		 * the new process start from 2 (1 belongs to the first system process) and go up.
		 * Do NOT reuse PIDs of the terminated processes.
		 * */
		if(input == "A")
		{
			myOS.addNewProcess(PID);
			PID++;
		}
		/* The currently running process has spent a time quantum using the CPU.
		 * Such process should be preempted to the end of the ready-queue.
		 * */
		else if(input == "Q")
		{
			myOS.nextProcess();
		}
		/* The process forks a child. The child is placed in the end of the ready-queue.
		 * */
		else if(input == "fork")
		{
			myOS.addNewChild(PID);
			PID++;
		}
		/* The process that is currently using the CPU terminates. Make sure you release
		 * the memory used by this process immediately. To avoid the appearance of the
		 * orphans, the system implements the cascading termination. If its parent is
		 * already waiting, the process terminates immediately and the parent becomes runnable
		 * (goes to the end of the ready-queue). If its parent hasn’t called wait yet, the
		 * process turns into zombie.
		 * */
		else if(input == "exit")
		{
			myOS.terminate();
		}
		/* The process wants to pause and wait for any of its child processes to terminate.
		 * Once the wait is over, the process goes to the end of the ready-queue. If the
		 * zombie-child already exists, the process proceeds right away (keeps using the
		 * CPU) and the zombie-child disappears. If more then one zombie-child existed,
		 * the system uses one of them (any!) to immediately restart the parent and other
		 * zombies keep waiting for the next wait from the parent.
		 * */
		else if(input == "wait")
		{
			myOS.processWait();
		}
		/* "d number file_name" The process that currently uses the CPU requests the hard disk #number.
		 * It wants to read or write file file_name.
		 * */
		else if(input.substr(0, 1) == "d")
		{
			string temp = input.substr(2);
			int i = 0;
			while(temp[i] != 32)
			{
				i++;
			}
			string temp2 = temp.substr(i+1);
			temp = temp.substr(0, i);
			int num = stoi(temp);
			myOS.requestIO(num, temp2);
		}
		/* The hard disk #number has finished the work for one process.
		 * */
		else if(input.substr(0, 1) == "D")
		{
			string temp = input.substr(2);
			int num = stoi(temp);
			myOS.IOprog(num);
		}
		/* The process that is currently using the CPU requests a memory operation
		 * for the logical address.
		 * */
		else if(input.substr(0, 1) == "m")
		{
			string temp = input.substr(2);
			int num = stoi(temp);
			myOS.allocateMem(num, time);
		}
		/* Shows what process is currently using the CPU and what processes are
		 * waiting in the ready-queue.
		 * */
		else if(input == "S r")
		{
			myOS.print_Ready();
		}
		/* Shows what processes are currently using the hard disks and what
		 * processes are waiting to use them. For each busy hard disk show the
		 * process that uses it and show its I/O-queue. Make sure to display
		 * the filenames (from the d command) for each process. The enumeration of
		 * hard disks starts from 0.
		 * */
		else if(input == "S i")
		{
			myOS.print_IO();
		}
		/* Shows the state of memory. For each used frame display the process number
		 * that occupies it and the page number stored in it. The enumeration of pages
		 * and frames starts from 0.
		 * */
		else if(input == "S m")
		{
			myOS.print_memory();
		}
		else if(input == "")
		{
		}
		else
		{
			cout << "Invalid input" << endl;
		}
		time++;
	}
}
