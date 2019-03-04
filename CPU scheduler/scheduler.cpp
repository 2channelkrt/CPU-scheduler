#pragma once
#include "scheduler.h"
#include <queue>
using namespace std;

int FCFS_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime)//assume first element in queue came first
{										//even if process came after its I/O operation
	if (queue.empty()) return -1;
	int next = queue.front();
	queue.pop();
	return next;
}
int SJF_nonpreemptive_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime)
{
	if (queue.empty()) return -1;
	int next = queue.front();
	int compare;
	queue.pop();
	while (!queue.empty())
	{
		compare = queue.front();
		if (pool.proc[compare].getCpuTime() < pool.proc[next].getCpuTime())
			next = compare;
		queue.pop();
	}
	return next;
}
int SJF_preemptive_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime)
{
	int compare;
	if (current == -1)
	{
		if (queue.size() >= 1)
		{
			current = queue.front();
			queue.pop();
		}
	}
	while (!queue.empty())
	{
		compare = queue.front();
		if (pool.proc[compare].getCpuTime() < pool.proc[current].getCpuTime())
			current = compare;
		queue.pop();
	}
	return current;
}
int Priority_nonpreemptive_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime)
{
	int next = queue.front();
	int compare;
	queue.pop();
	while (!queue.empty())
	{
		compare = queue.front();
		if (pool.proc[compare].getPriority() < pool.proc[next].getPriority())
			next = compare;
		queue.pop();
	}
	return next;
}
int Priority_preemptive_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime)
{
	int compare;
	if (current == -1)
	{
		if (queue.size() >= 1)
		{
			current = queue.front();
			queue.pop();
		}
	}
	while (!queue.empty())
	{
		compare = queue.front();
		if (pool.proc[compare].getPriority() < pool.proc[current].getPriority())
			current = compare;
		queue.pop();
	}
	return current;
}
int RR_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime)//assume first element in queue is next.
{
	if (current == -1)
	{
		nowTime = 0;
		if (queue.empty()) return current;
		else
		{
			current = queue.front();
			queue.pop();
			return current;
		}
	}
	if (limitTime == *nowTime)
	{
		current = queue.front();
		queue.pop();
		nowTime = 0;
	}
	return current;
}