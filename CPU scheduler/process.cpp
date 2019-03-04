#pragma once
#include "process.h"
#include "CUSTOMVALUE.h"
#include <stdio.h>
#include <cstdlib>
void process::printProcessInfo()
{
	printf("pid:%3d arriveTime:%3d cpuTime:%d io:%3d priority:%3d done: %s\n", pid, arriveTime, cpuTime, IONum, priority, done ? "true" : "false");
	printIOInfo();
}

void process::setIOProcess()
{
	if (IONum != 0)
	{
		this->io = new IOProcess[IONum];
		if (initIOProcess() == false) printf("io init failed\n");
	}
	else
		this->io = NULL;
}

bool process::initIOProcess()
{
	for (int i = 0; i < IONum; i++)
	{
		io[i].setTime((rand() % IOMAXTIME) + 1);
		if (i == 0)
		{
			int temp = rand() % getCpuTime() + 1;
			if (temp == getCpuTime())
			{
				setCpuTime(temp + 1);
			}
			io[i].setStartTime(temp);
		}
		else
		{
			int temp = getCpuTime();
			while (io[i - 1].getStartTime() >= getCpuTime())
			{
				temp += 2;
				setCpuTime(temp);
			}
			io[i].setStartTime(io[i - 1].getStartTime() + rand() % (getCpuTime() - io[i - 1].getStartTime()) + 1);
			while (io[i].getStartTime() >= getCpuTime() - 1)
			{
				setCpuTime(++temp);
			}
		}//set eaach io operations' start time in the way that
		// every io operation doesn't start simultaneously,
		// nor after all the cpu time is done.

		io[i].setDone(false);
	}
	return true;
}

void process::printIOInfo()
{
	if (IONum == 0)
		printf("no I/O for this process\n");
	else
	{
		for (int i = 0; i < IONum; i++)
		{
			printf("\tnum: %3d startTime: %3d time:%3d done: %5s\n", i, io[i].getStartTime(), io[i].getTime(), io[i].getDone() ? "true" : "false");
		}
	}
}

void job::printInfo()
{
	printf("////////////////pool info////////////////\n");
	for (int i = 0; i < this->size; i++)
	{
		proc[i].printProcessInfo();
	}
	printf("////////////////pool info ended//////////\n");
}
int job::getPidOfMinArriveTime()
{
	int currentPid = -1;
	int currentArriveTime = INFINIT;
	for (int i = 0; i < getSize(); i++)
	{
		if (proc[i].getDone() == false && proc[i].getArriveTime() < currentArriveTime)
			currentPid = i;
	}
	return currentPid;
}

int job::getPidOfHighestPriority()
{
	int currentPid = -1;
	int currentPriority = -INFINIT;
	for (int i = 0; i < getSize(); i++)
	{
		if (proc[i].getDone() == false && proc[i].getPriority() < currentPriority)
			currentPid = i;
	}
	return currentPid;
}

bool job::initProcess()
{
	for (int i = 0; i < this->size; i++)
	{
		proc[i].setPid(i);
		proc[i].setArriveTime(rand() % this->size);
		proc[i].setCpuTime((rand() % MAXCPUTIME) + 1);//////////////////////fix if desired
		proc[i].setPriority(rand() % this->size);
		proc[i].setWaitingTime(-1);
		proc[i].setTurnaroundTime(-1);
		proc[i].setDone(false);

		proc[i].setIONum(rand() % (IOMAXSIZE + 1));
		proc[i].setIOProcess();//null if zero
		proc[i].setR(rand() % 256);
		proc[i].setG(rand() % 256);
		proc[i].setB(rand() % 256);
	}


	return true;
}

void IOProcess::clone(IOProcess source)
{
	this->startTime = source.startTime;
	this->time = source.time;
	this->done = source.done;
}

void process::clone(process source)
{
	if (source.IONum != 0)
	{
		this->io = new IOProcess[source.IONum];

		for (int i = 0; i < source.IONum; i++)
		{
			this->io[i].clone(source.io[i]);
		}
	}
	this->pid = source.pid;
	this->arriveTime = source.arriveTime;
	this->cpuTime = source.cpuTime;
	this->IONum = source.IONum;
	this->priority = source.priority;
	this->waitingTime = source.waitingTime;
	this->turnaroundTime = source.turnaroundTime;
	this->done = source.done;
	this->r = source.r;
	this->g = source.g;
	this->b = source.b;
}

void job::clone(job source)
{
	this->proc = new process[source.size];
	for (int i = 0; i < source.size; i++)
	{
		this->proc[i].clone(source.proc[i]);
	}
	this->size = source.size;
}