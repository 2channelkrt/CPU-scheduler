# CPU-Scheduler

CPU scheduler visualizer on visual studio with [allegro](https://liballeg.org/)

# How To Use
1. Configure CUSTOMVALUE.h and run!

## custom values
![alt_text](https://github.com/2channelkrt/CPU-scheduler/blob/master/value_example.PNG)
* IOMAXSIZE    : maximum number of I/O operation for given task
* IOMAXTIME    : maximum time of each I/O operation for given task
* MAXCPUTIME   : maximum CPU time for given task
* TIMEQUANTUM  : time quantum for RR(Round Robin) scheduling algorithm.

# Result Example

![alt text](https://github.com/2channelkrt/CPU-scheduler/blob/master/scheduler_example.PNG)

# Notice

Last time I checked, this runs only if run under Microsoft Visual Studio. Probably static library linking problem, but my priority is low for this issue.
