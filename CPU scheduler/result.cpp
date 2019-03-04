#include "result.h"
#include "CUSTOMVALUE.h"
void result::drawGhantChart(ALLEGRO_FONT *timeFont, ALLEGRO_FONT*processFont, job pool)
{
	int Yoffset = (this->num + 1)*CHART_Y_DISTANCE;
	int time = 0;
	int previousProc = -3;//-2 means end of current process.
	al_draw_textf(timeFont, al_map_rgb(255, 255, 255), CHART_X_OFFSET, Yoffset - BOXSIZE, ALLEGRO_ALIGN_LEFT, "%s", name);
	while (!currentProc.empty())
	{
		if (currentProc.front() >= 0)
		{
			al_draw_filled_rectangle(time*BOXSIZE + CHART_X_OFFSET, Yoffset - BOXSIZE / 2, (time + 1)*BOXSIZE + CHART_X_OFFSET, Yoffset + BOXSIZE / 2\
				, (al_map_rgb(pool.proc[this->currentProc.front()].getR()\
					, pool.proc[this->currentProc.front()].getG()\
					, pool.proc[this->currentProc.front()].getB())));//box print
		}
		if (this->currentProc.front() != previousProc)//if process changed, label time
		{
			al_draw_textf(timeFont, al_map_rgb(255, 255, 255), time * BOXSIZE + CHART_X_OFFSET, Yoffset + BOXSIZE / 2 + TIMEFONT_Y_OFFSET, ALLEGRO_ALIGN_CENTRE, "%d", time);//time print
			al_draw_textf(processFont, al_map_rgb(255, 255, 255), time*BOXSIZE + CHART_X_OFFSET + PROCESSNUM_X_OFFSET, Yoffset - BOXSIZE / 2 + PROCESSNUM_Y_OFFSET, ALLEGRO_ALIGN_CENTRE, "%d", this->currentProc.front());//process number print
		}
		previousProc = this->currentProc.front();
		currentProc.pop();
		if (this->currentProc.front() == -2)
		{
			al_draw_textf(processFont, al_map_rgb(255, 255, 255), time*BOXSIZE + CHART_X_OFFSET + PROCESSNUM_X_OFFSET + PROCESSDONE_X_OFFSET, Yoffset - BOXSIZE / 2 + PROCESSNUM_Y_OFFSET, ALLEGRO_ALIGN_CENTRE, "/");
			currentProc.pop();
		}
		time++;

	}
	al_draw_textf(timeFont, al_map_rgb(255, 255, 255), time*BOXSIZE + CHART_X_OFFSET, Yoffset + BOXSIZE / 2 + TIMEFONT_Y_OFFSET, ALLEGRO_ALIGN_CENTRE, "%d", time);//last time print

}

void result::printResult()
{
	printf("Avg.WaitingTime: %.2f ", averageWaitingTime);
	printf("Avg.TurnaroundTime: %.2f ", averageTurnaroundTime);
	printf("Total time: %d ", totalTime);
	printf("util: %.2f\n", 100 * utilTime / (float)totalTime);
}
