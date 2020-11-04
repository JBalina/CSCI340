//Jonathan Balina CSCI340

#include"PCB.h"

PCB::PCB()
{
	isZombie = false;
	hasParent = false;
}

PCB::PCB(int nPID)
{
	PID = nPID;
	isZombie = false;
	hasParent = false;
}

bool PCB::operator==(int match_PID)
{
	if(PID == match_PID)
		return true;
	else
		return false;
}

bool PCB::operator==(PCB match_PCB)
{
	if(PID == match_PCB.PID)
		return true;
	else
		return false;
}
