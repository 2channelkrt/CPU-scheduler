#pragma once
#include "evaluate.h"
#include "CUSTOMVALUE.h"
#include <stdio.h>
#include <vector>

using namespace std;

int processIOCall(process process)
{
	int currentIO = findCurrentIO(process);
	if (currentIO == -1) return -1;
	for (int i = currentIO; i < process.getIONum(); i++)
	{
		if (process.io[i].getStartTime() == 0)//we need to make sure to decrease ioTime each time
			return i;
	}
	return -1;
}
queue<int> popProcessFromQueue(queue<int>* before, int pop)
{
	queue<int> after;
	while (!before->empty())
	{
		if (before->front() != pop)
		{
			after.push(before->front());
		}
		before->pop();
	}
	return after;
}
queue<int> increaseWaitingTime(job* pool, queue<int> readyBefore)
{
	queue<int> readyAfter;
	while (!readyBefore.empty())
	{
		pool->proc[readyBefore.front()].increaseWaitingTime();
		readyAfter.push(readyBefore.front());
		readyBefore.pop();
	}
	return readyAfter;
}
int findCurrentIO(process process)
{
	for (int i = 0; i < process.getIONum(); i++)
	{
		if (process.io[i].getDone() == false)//check
			return i;
	}
	return -1;
}
queue<int> increaseIOTime(job* pool, queue<int>* ready, queue<int> waitBefore)
{
	queue<int> waitAfter;
	int currentIO;
	int currentProc;
	while (!waitBefore.empty())
	{
		currentProc = waitBefore.front();
		currentIO = findCurrentIO(pool->proc[currentProc]);
		if (currentIO == -1)
		{
			printf("increaseIOTime ERROR\n");
		}
		pool->proc[currentProc].io[currentIO].decreaseTime();//check
		if (pool->proc[currentProc].io[currentIO].getTime() == 0)//check
		{
			pool->proc[currentProc].io[currentIO].setDone(true);
			ready->push(currentProc);
		}
		else
			waitAfter.push(currentProc);
		waitBefore.pop();
	}
	return waitAfter;
}
bool ended(job pool)
{

	for (int i = 0; i < pool.getSize(); i++)
	{
		if (pool.proc[i].getDone() == false) return false;
	}
	return true;
}

void printQueue(queue<int> input)
{
	queue<int> output;
	printf("<");
	while (!input.empty())
	{
		printf("%d, ", input.front());
		output.push(input.front());
		input.pop();
	}
	printf(">\n");
	swap(output, input);
}

result schedule(job pool, int(*scheduler)(int, queue<int>, job, int, int*), bool preempt)
{//if process goes into i/o, it comes into ready queue after it's done its i/o
	queue<int> ready;
	queue<int> wait;
	result result;

	bool needNewProcess = true;
	int time = 0;
	int currentProcess = -1; //-1 means idl
	int RRtime = 0;
	while (!ended(pool))//new time
	{
		for (int i = 0; i < pool.getSize(); i++)//push process into ready
		{										//queue when new process arrive
			if (pool.proc[i].getArriveTime() == time)
				ready.push(i);
		}

		//check if we need new process//
		if (currentProcess == -1)
		{//if cpu is idle
			needNewProcess = true;
		}
		else if (processIOCall(pool.proc[currentProcess]) != -1)
		{//if current process calls IO
			wait.push(currentProcess);
			currentProcess = -1;//inserted
			needNewProcess = true;
		}
		else if (pool.proc[currentProcess].getCpuTime() == 0)
		{//current process is done
			pool.proc[currentProcess].setTurnaroundTime(time - pool.proc[currentProcess].getArriveTime());
			pool.proc[currentProcess].setDone(true);
			currentProcess = -1;
			needNewProcess = true;
			result.addCurrentProc(-2);
			if (ended(pool)) break;

		}
		else if (preempt && ready.empty() == false && (*scheduler)(currentProcess, ready, pool, TIMEQUANTUM, &RRtime) != currentProcess)
		{//if current process is preempted or RR
			ready.push(currentProcess);
			needNewProcess = true;
		}

		if (needNewProcess == true)//calling new process
		{
			if (ready.empty())//no process in queue
			{
				currentProcess = -1;
			}
			else
			{
				currentProcess = (*scheduler)(currentProcess, ready, pool, TIMEQUANTUM, &RRtime);
				ready = popProcessFromQueue(&ready, currentProcess);
				RRtime = 0;
				needNewProcess = false;
			}
		}
		//executing current process//
		time++;
		RRtime++;

		if (currentProcess != -1)//decrease start time for current process
		{
			pool.proc[currentProcess].decreaseCpuTime();
			int temp = findCurrentIO(pool.proc[currentProcess]);
			if (temp != -1)//-1 means either there's no I/O, or all done.
			{
				for (int i = temp; i < pool.proc[currentProcess].getIONum(); i++)
				{
					pool.proc[currentProcess].io[i].decreaseStartTime();
				}
			}
		}


		//updating result//
		result.increaseTotalTime();
		if (currentProcess != -1) result.increaseUtilTime();
		result.addCurrentProc(currentProcess);

		ready = increaseWaitingTime(&pool, ready);

		wait = increaseIOTime(&pool, &ready, wait);
		/*
		printf("//////////////////////////////////////\n");
		printf("current RRtime: %d -> %d\n", RRtime-1, RRtime);
		printf("current time: %d -> %d current process:%d\n",time-1, time, currentProcess);
		pool.printInfo();
		printf("ready: ");
		printQueue(ready);
		printf("wait: ");
		printQueue(wait);
		*/


	}

	int totalWaitingTime = 0;
	int totalTurnaroundTime = 0;

	for (int i = 0; i < pool.getSize(); i++)
	{
		totalWaitingTime += pool.proc[i].getWaitingTime();
		totalTurnaroundTime += pool.proc[i].getTurnaroundTime();
	}

	result.setAverageWaitingTime(totalWaitingTime / (float)result.getTotalTime());
	result.setAverageTurnaroundTime(totalTurnaroundTime / (float)result.getTotalTime());

	return result;
}

