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
		if(input == "A")
		{
			myOS.addNewProcess(PID);
			PID++;
		}
		else if(input == "Q")
		{
			myOS.nextProcess();
		}
		else if(input == "fork")
		{
			myOS.addNewChild(PID);
			PID++;
		}
		else if(input == "exit")
		{
			myOS.terminate();
		}
		else if(input == "wait")
		{
			myOS.processWait();
		}
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
		else if(input.substr(0, 1) == "D")
		{
			string temp = input.substr(2);
			int num = stoi(temp);
			myOS.IOprog(num);
		}
		else if(input.substr(0, 1) == "m")
		{
			string temp = input.substr(2);
			int num = stoi(temp);
			myOS.allocateMem(num, time);
		}
		else if(input == "S r")
		{
			myOS.print_Ready();
		}
		else if(input == "S i")
		{
			myOS.print_IO();
		}
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
