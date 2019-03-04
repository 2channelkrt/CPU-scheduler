#pragma once

#include <stdio.h>
class IOProcess
{
public:
	IOProcess()
		:startTime(0), time(0), done(false) {}

	void setTime(int time) { this->time = time; }
	void setDone(bool done) { this->done = done; }
	void setStartTime(int time) { this->startTime = time; }
	void decreaseTime() { this->time--; }
	void decreaseStartTime() { this->startTime--; }

	int getTime() { return this->time; }
	bool getDone() { return this->done; }
	int getStartTime() { return this->startTime; }

	void clone(IOProcess source);

private:
	int startTime;
	int time;
	bool done;
};

class process
{
public:
	process()
		:pid(0), arriveTime(0), cpuTime(0), priority(0), waitingTime(0), turnaroundTime(0) {}

	void printProcessInfo();
	void setPid(int pid) { this->pid = pid; }
	void setArriveTime(int arriveTime) { this->arriveTime = arriveTime; }
	void setCpuTime(int cpuTime) { this->cpuTime = cpuTime; }
	void setPriority(int priority) { this->priority = priority; }
	void setWaitingTime(int waitingTime) { this->waitingTime = waitingTime; }
	void increaseWaitingTime() { this->waitingTime++; }
	void decreaseCpuTime() { this->cpuTime--; }
	void setTurnaroundTime(int turnaroundTime) { this->turnaroundTime = turnaroundTime; }
	void setDone(bool done) { this->done = done; }
	void setIONum(int num) { this->IONum = num; }
	void setIOProcess();
	void setR(int r) { this->r = r; }
	void setG(int g) { this->g = g; }
	void setB(int b) { this->b = b; }

	bool initIOProcess();
	void printIOInfo();

	int getPid() { return this->pid; }
	int getArriveTime() { return this->arriveTime; }
	int getCpuTime() { return this->cpuTime; }
	int getPriority() { return this->priority; }
	int getWaitingTime() { return this->waitingTime; }
	int getTurnaroundTime() { return this->turnaroundTime; }
	bool getDone() { return this->done; }
	int getIONum() { return this->IONum; }
	int getR() { return this->r; }
	int getG() { return this->g; }
	int getB() { return this->b; }

	void clone(process source);

	IOProcess* io;
private:
	int pid;
	int arriveTime;
	int cpuTime;
	int IONum;
	int priority;
	int waitingTime;	//init to -1
	int turnaroundTime;	//init to -1
	bool done;
	int r;
	int g;
	int b;
};

class job
{
public:
	job()
	{
		this->proc = nullptr;
		this->size = -1;
	}
	job(int size)
	{
		this->size = size;
		proc = new process[size];
		if (!initProcess()) printf("process init failed\n");
	}
	bool initProcess();
	int getSize() { return this->size; }

	void printInfo();
	int getPidOfHighestPriority();//deprecated
	int getPidOfMinArriveTime();//deprecated

	void clone(job source);

	process* proc;
private:
	int size;
};