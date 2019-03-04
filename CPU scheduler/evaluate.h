#pragma once
#include "process.h"
#include "result.h"
#include <queue>

int processIOCall(process process);
queue<int> popProcessFromQueue(queue<int>* before, int pop);
queue<int> increaseWaitingTime(job* pool, queue<int> readyBefore);
int findCurrentIO(process process);
queue<int> increaseIOTime(job* pool, queue<int>* ready, queue<int> waitBefore);
bool ended(job pool);
result schedule(job pool, int(*scheduler)(int, queue<int>, job, int, int*), bool preempt);