#pragma once

#include <stdio.h>
#include "process.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <queue>
using namespace std;

class result
{

public:
	result()
	{
		averageWaitingTime = -1;
		averageTurnaroundTime = -1;
		totalTime = 0;
		utilTime = 0;
	}
	float getAverageWaitingTime() { return averageWaitingTime; }
	float getAverageTurnaroundTime() { return averageTurnaroundTime; }
	int getTotalTime() { return totalTime; }
	int getUtilTime() { return utilTime; }
	int getNum() { return num; }
	const char* getName() { return name; }

	void setAverageWaitingTime(float num) { this->averageWaitingTime = num; }
	void setAverageTurnaroundTime(float num) { this->averageTurnaroundTime = num; }
	void setTotalTime(int num) { this->totalTime = num; }
	void setUtilTime(int num) { this->utilTime = num; }
	void setNum(int num) { this->num = num; }
	void setName(const char* name) { this->name = name; }

	void increaseTotalTime() { this->totalTime++; }
	void increaseUtilTime() { this->utilTime++; }


	void addCurrentProc(int num) { this->currentProc.push(num); }
	void drawGhantChart(ALLEGRO_FONT *timeFont, ALLEGRO_FONT *processFont, job pool);
	void printResult();

private:
	float averageWaitingTime;
	float averageTurnaroundTime;

	int totalTime;
	int utilTime;

	queue<int> currentProc;
	int num;

	const char* name;
};