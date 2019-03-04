#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "evaluate.h"
#include "scheduler.h"
#include <cstdlib>
#include "CUSTOMVALUE.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

int main()
{
	al_init();

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	ALLEGRO_FONT* timeFont = al_load_font("font.ttf", TIMEFONTSIZE, ALLEGRO_TTF_NO_KERNING);
	ALLEGRO_FONT* processFont = al_load_font("font.ttf", PROCESSFONTSIZE, ALLEGRO_TTF_NO_KERNING);

	srand(time(NULL));
	int poolSize;
	printf("task size: ");
	scanf_s("%d", &poolSize);
	//adsf
	ALLEGRO_DISPLAY* display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
	//al_clear_to_color(al_map_rgb(0, 0, 0));
	job pool(poolSize);

	pool.printInfo();

	job FCFS_Job;
	FCFS_Job.clone(pool);

	job SJF_nonpreemptive_Job;
	SJF_nonpreemptive_Job.clone(pool);

	job Priority_nonpreemptive_Job;
	Priority_nonpreemptive_Job.clone(pool);

	job RR_Job;
	RR_Job.clone(pool);

	job Priority_preemptive_Job;
	Priority_preemptive_Job.clone(pool);

	job SJF_preemptive_Job;
	SJF_preemptive_Job.clone(pool);

	result FCFS = schedule(FCFS_Job, FCFS_scheduler, false);
	FCFS.setNum(0);
	FCFS.setName("FCFS");
	printf("FCFS Result -- ");
	FCFS.printResult();
	FCFS.drawGhantChart(timeFont, processFont, FCFS_Job);

	result SJF_nonpreemptive = schedule(SJF_nonpreemptive_Job, SJF_nonpreemptive_scheduler, false);
	SJF_nonpreemptive.setNum(1);
	SJF_nonpreemptive.setName("SJF_nonrpeemptive");
	printf("SJF_Nonpreemptive Result -- ");
	SJF_nonpreemptive.printResult();
	SJF_nonpreemptive.drawGhantChart(timeFont, processFont, SJF_nonpreemptive_Job);

	result Priority_nonpreemptive = schedule(Priority_nonpreemptive_Job, Priority_nonpreemptive_scheduler, false);
	Priority_nonpreemptive.setNum(2);
	Priority_nonpreemptive.setName("Priority_nonpreemptive");
	printf("Priority_Nonpreemptive -- ");
	Priority_nonpreemptive.printResult();
	Priority_nonpreemptive.drawGhantChart(timeFont, processFont, Priority_nonpreemptive_Job);

	result RR = schedule(RR_Job, RR_scheduler, true);
	RR.setNum(3);
	RR.setName("RR");
	printf("Round Robin -- ");
	RR.printResult();
	RR.drawGhantChart(timeFont, processFont, RR_Job);

	result Priority_preemptive = schedule(Priority_preemptive_Job, Priority_preemptive_scheduler, true);
	Priority_preemptive.setNum(4);
	Priority_preemptive.setName("Priority_Preemptive");
	printf("Priority_Preemptive -- ");
	Priority_preemptive.printResult();
	Priority_preemptive.drawGhantChart(timeFont, processFont, Priority_preemptive_Job);

	result SJF_preemptive = schedule(SJF_preemptive_Job, SJF_preemptive_scheduler, true);
	SJF_preemptive.setNum(5);
	SJF_preemptive.setName("SJF_preemptive");
	printf("SJF_Preemptive -- ");
	SJF_preemptive.printResult();
	SJF_preemptive.drawGhantChart(timeFont, processFont, SJF_preemptive_Job);

	al_flip_display();

	ALLEGRO_PATH* path = al_create_path_for_directory("./");
	al_set_path_filename(path, "screenshot123");
	if (!al_set_path_extension(path, ".png")) printf("al_set_path_extension failed\n");
	const char* path_cstr = al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP);
	if (!al_save_bitmap(path_cstr, al_get_target_bitmap())) printf("screenshot failed\n");
	system("pause");

	al_destroy_path(path);
	al_destroy_font(timeFont);
	al_destroy_font(processFont);
	al_destroy_display(display);


	return 0;
}