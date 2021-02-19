#ifndef SCHEDULE_H
#define SCHEDULE_H
//#define GOODNESS
#define PURE_SJF

#define A 5

#include "macros.h"
#include "list.h"
#include "privatestructs.h"

struct thread_info;

/* ---------------- Do NOT Touch -------------- */
/* Sleep Types */
enum sleep_type
{
	SLEEP_NORMAL,
	SLEEP_NONINTERACTIVE,
	SLEEP_INTERACTIVE,
	SLEEP_INTERRUPTED
};

/* task_struct */
struct task_struct
{
	struct thread_info *thread_info;		/* Information about the thread */
	unsigned int time_slice;				/* Timeslice values */
	enum sleep_type sleep_type;				/* What type of sleep task is in */
	int need_reschedule;					/* Flag, set if task needs to
											   have schedule called */
	struct task_struct *prev, *next;	/* Used to link the task struct in the
										   runqueue. Make sure to set them to
										   NULL when the process is not in the
										   runqueue */
/* ---------------- Do NOT Touch END-------------- */

	unsigned long long exp_burst;
	double goodness;
	unsigned long long start_time;
	unsigned long long end_time;
	unsigned long long burst; //end_time - start_time
	unsigned long long rq_enter_time;
	unsigned long long waiting_in_rq;
	unsigned long long history_exp_burst;
	int flag;
};
/* runqueue */
struct runqueue {
    unsigned long    nr_running;			/* number of runnable tasks */
	struct task_struct *head;
};

/*----------------------- System Calls ------------------------------*/
/* These calls are provided by the VM for your
 * convenience, and mimic system calls provided
 * normally by Linux
 */
void context_switch(struct task_struct *next);
unsigned long long sched_clock();

/*------------------YOU MAY EDIT BELOW THIS LINE---------------------*/
/*------------------- User Defined Functions -------------------------*/
/*-------------These functions MUST be defined for the VM-------------*/
void initschedule(struct runqueue *newrq, struct task_struct *seedTask);
void killschedule();
void schedule();
void activate_task(struct task_struct *p);
void deactivate_task(struct task_struct *p);
void scheduler_tick(struct task_struct *p);
void sched_fork(struct task_struct *p);
void wake_up_new_task(struct task_struct *p);

#endif
