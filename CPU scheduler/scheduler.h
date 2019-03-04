#pragma once
#include "process.h"
#include <queue>
using namespace std;

int FCFS_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime);//assume first element in queue came first
int SJF_nonpreemptive_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime);
int SJF_preemptive_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime);
int Priority_nonpreemptive_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime);
int Priority_preemptive_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime);
int RR_scheduler(int current, queue<int> queue, job pool, int limitTime, int* nowTime);//assume first element in queue is next.;
