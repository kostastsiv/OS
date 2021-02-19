/* schedule.c
 * This file contains the primary logic for the
 * scheduler.
 */
#include "schedule.h"
#include "macros.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define NEWTASKSLICE (NS_TO_JIFFIES(100000000))

/* Local Globals
 * rq - This is a pointer to the runqueue that the scheduler uses.
 * current - A pointer to the current running task.
 */
struct runqueue *rq;
struct task_struct *current;

/* External Globals
 * jiffies - A discrete unit of time used for scheduling.
 *			 There are HZ jiffies in a second, (HZ is
 *			 declared in macros.h), and is usually
 *			 1 or 10 milliseconds.
 */
extern long long jiffies;
extern struct task_struct *idle;

/*-----------------Initilization/Shutdown Code-------------------*/
/* This code is not used by the scheduler, but by the virtual machine
 * to setup and destroy the scheduler cleanly.
 */

 /* initscheduler
  * Sets up and allocates memory for the scheduler, as well
  * as sets initial values. This function should also
  * set the initial effective priority for the "seed" task
  * and enqueu it in the scheduler.
  * INPUT:
  * newrq - A pointer to an allocated rq to assign to your
  *			local rq.
  * seedTask - A pointer to a task to seed the scheduler and start
  * the simulation.
  */
void initschedule(struct runqueue *newrq, struct task_struct *seedTask)
{
	seedTask->next = seedTask->prev = seedTask;
	newrq->head = seedTask;
	newrq->nr_running++;

    seedTask->exp_burst = 0;
	seedTask->start_time = 0;
	seedTask->goodness = 1;
	seedTask->end_time = 0;
	seedTask->burst = 0; //end_time - start_time
	seedTask->rq_enter_time = 0;
	seedTask->waiting_in_rq = 0;
	seedTask->flag = 0;
	seedTask->history_exp_burst = 0;
}

/* killschedule
 * This function should free any memory that
 * was allocated when setting up the runqueu.
 * It SHOULD NOT free the runqueue itself.
 */
void killschedule()
{
    unsigned long num_tasks = rq->nr_running;
    struct task_struct *temp;
    for (unsigned long i = 1; i < num_tasks;i++){
      temp = rq->head;
      rq->head->next->prev = rq->head->prev;
      rq->head->prev->next = rq->head->next;
      temp->next = NULL;
      temp->prev = NULL;
    }
    rq->head->next = NULL;
    rq->head->prev = NULL;
	return;
}


void print_rq () {
	struct task_struct *curr;

	printf("Rq: \n");
	rq->head = rq->head->next;
	curr = rq->head;
	if (curr)
		printf("%p", curr);
	while(curr->next != rq->head) {
		curr = curr->next;
		printf(", %p", curr);
	};
	printf("\n");
}

/*-------------Scheduler Code Goes Below------------*/
/* This is the beginning of the actual scheduling logic */

/* schedule
 * Gets the next task in the queue
 */
void schedule()
{
  struct task_struct *temp;
	struct task_struct *min;
	#ifdef GOODNESS
	struct task_struct *max;
	#endif
//	printf("In schedule\n");
//	print_rq();


#ifdef PURE_SJF
	current->end_time = sched_clock();
	current->burst = current->end_time - current->start_time;
	if(current-> flag == 0){
  	current->exp_burst = ((current->burst) + A*(current->exp_burst))/(1 + A);
    }
    else {
      current->exp_burst = ((current->burst) + A*(current->history_exp_burst))/(1 + A);
    }
	current->need_reschedule = 0; /* Always make sure to reset that, in case *
								 * we entered the scheduler because current*
								 * had requested so by setting this flag   */
  temp = rq->head;
	min = temp;

	for(int i =0; i < rq->nr_running; i++) {
		if(temp->next->exp_burst < min->exp_burst) {
			min = temp->next;
		}
		temp = temp->next;
	}

	for(int i =0; i < rq->nr_running; i++) {
		temp->goodness = (double)(1+temp->exp_burst)/(double)(1+min->exp_burst)*1;
		temp=temp->next;
	}


	temp = rq->head;
	min = temp;

	if (rq->nr_running == 1) {
			min->flag = 1;
			context_switch(min);
	}
	else {
		for(int i =0; i < rq->nr_running; i++) {
			if(temp->next->goodness < min->goodness) {
				min = temp->next;
			}
			temp = temp->next;
		}
		if(min == current) {
			current->flag = 1;
			context_switch(min);
		}
		else {
			current->flag = 0;
			current->history_exp_burst = current->exp_burst;
			min->start_time = sched_clock();
			context_switch(min);
		}
	}
#endif

#ifdef GOODNESS
current->end_time = sched_clock();
current->burst = current->end_time - current->start_time;
if(current-> flag == 0){
  	current->exp_burst = ((current->burst) + A*(current->exp_burst))/(1 + A);
}
else {
      current->exp_burst = ((current->burst) + A*(current->history_exp_burst))/(1 + A);
}
current->rq_enter_time = sched_clock();

//printf("Exp_burst: %lld\n",current->exp_burst);
current->need_reschedule = 0; /* Always make sure to reset that, in case *
							 * we entered the scheduler because current*
							 * had requested so by setting this flag   */
temp = rq->head;
for(int i=0; i < rq->nr_running; i++) {
	temp->waiting_in_rq = sched_clock() - temp->rq_enter_time;
	temp=temp->next;
}
temp = rq->head;
min = temp;

for(int i =0; i < rq->nr_running; i++) {
	if(temp->next->exp_burst < min->exp_burst) {
		min = temp->next;
	}
	temp = temp->next;
}

temp = rq->head;
min = temp;

temp = rq->head;
max = temp;

for(int i = 0; i < rq->nr_running; i++) {
	if(temp->next->waiting_in_rq > max->waiting_in_rq) {
		max = temp->next;
	}
	temp = temp->next;
}

temp = rq->head;

for(int i =0; i < rq->nr_running; i++) {
	current->goodness = ((1+current->exp_burst)/(double)(1+min->exp_burst)) *((1+max->waiting_in_rq)/(double)(1+current->waiting_in_rq));
	temp=temp->next;
}


temp = rq->head;
min = temp;


if (rq->nr_running == 1) {
		min->flag = 1;
		context_switch(min);
}
else {
	for(int i =0; i < rq->nr_running; i++) {
		if(temp->next->goodness <= min->goodness) {
			min = temp->next;
		}
		temp = temp->next;
	}
	if(min == current) {
		current->flag = 1;
		context_switch(min);
	}
	else {
		current->flag = 0;
		current->history_exp_burst = current->exp_burst;
		min->waiting_in_rq = 0;
		min->start_time = sched_clock();
		current->rq_enter_time = min->start_time;
		context_switch(min);
	}
}
#endif
}

/* sched_fork
 * Sets up schedule info for a newly forked task
 */
void sched_fork(struct task_struct *p)
{
	p->time_slice = 100;
	p->exp_burst = 0;
	p->goodness = 1;
	p->start_time = 0;
	p->end_time = 0;
	p->burst = 0;
	p->rq_enter_time = 0;
	p->waiting_in_rq = 0;
	p->flag = 0;
	p->history_exp_burst = 0;
}

/* scheduler_tick
 * Updates information and priority
 * for the task that is currently running.
 */
void scheduler_tick(struct task_struct *p)
{
	schedule();
}

/* wake_up_new_task
 * Prepares information for a task
 * that is waking up for the first time
 * (being created).
 */
void wake_up_new_task(struct task_struct *p)
{
	p->rq_enter_time = sched_clock();
	p->next = rq->head->next;
	p->prev = rq->head;
	p->next->prev = p;
	p->prev->next = p;

	rq->nr_running++;
}

/* activate_task
 * Activates a task that is being woken-up
 * from sleeping.
 */
void activate_task(struct task_struct *p)
{
	p->rq_enter_time = sched_clock();
	p->next = rq->head->next;
	p->prev = rq->head;
	p->next->prev = p;
	p->prev->next = p;

	rq->nr_running++;
}

/* deactivate_task
 * Removes a running task from the scheduler to
 * put it to sleep.
 */
void deactivate_task(struct task_struct *p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	p->next = p->prev = NULL; /* Make sure to set them to NULL *
							   * next is checked in cpu.c      */

	rq->nr_running--;
}
