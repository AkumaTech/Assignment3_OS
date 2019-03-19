/*
Priority round robin
Miguel Hernandez
Miguel Manuel
Jose Avina
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "task.h"
#include "cpu.h"
#include "schedulers.h"

#define TIME 10

struct node** head = NULL;
struct node** tail;

void destroy(int p)//destroys the memory in the list
{
	struct node* h = head[p];
	struct node* t = tail[p];
	t = h;
	h = h->next;
	free(t);
	while(h)
	{
		t = h;
		h = h->next;
		free(t->task->name);
		free(t->task);
		free(t);
	}
}

void removeNode(struct node* n)//removes the information of the node
{
	free(n->task->name);
	free(n->task);
	free(n);
}

Task* newTask(char* name, int priority, int burst)//creates a new task
{
	Task* n_task = (Task*)malloc(sizeof(Task));
	n_task->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
	strcpy(n_task->name, name);
	n_task->priority = priority;
	n_task->burst = burst;
	n_task->tid = 0;
	return n_task;
}

void add(char* name, int priority, int burst)//adds the task into a list
{
	int i;
	if(head == NULL)
	{
		head = (struct node**)malloc(sizeof(struct node*)*(MAX_PRIORITY+1));
		tail = (struct node**)malloc(sizeof(struct node*)*(MAX_PRIORITY+1));
		for(i = 0; i <= MAX_PRIORITY; ++i)
			head[i] = tail[i] = NULL;
	}
	if(priority < MIN_PRIORITY || priority > MAX_PRIORITY)
	{
		printf("[error], invalid priority\n");
		return;
	}
	if(head[priority] == NULL)
	{
		head[priority] = (struct node*)malloc(sizeof(struct node));
		head[priority]->task = NULL;
		head[priority]->next = NULL;
		tail[priority] = head[priority];
	}
	tail[priority]->next = (struct node*)malloc(sizeof(struct node));
	tail[priority] = tail[priority]->next;
	tail[priority]->task = newTask(name, priority, burst);
	tail[priority]->next = NULL;
}

void scheduleP(int priority)//find the priority of the task and gets it ready for the 
//scheduler
{
	int s;
	struct node* tp;
	struct node* h = head[priority];
	struct node* t = tail[priority];
	while(h->next)
	{
		s = (TIME < h->next->task->burst)?TIME:h->next->task->burst;
		run(h->next->task, s);
		if(h->next->task->burst == s)
		{
			tp = h->next;
			h->next = h->next->next;
			removeNode(tp);
		}
		else
		{
			h->next->task->burst -= s;
			t->next = h->next;
			t = t->next;
			h->next = h->next->next;
			t->next = NULL;
		}
	}
	destroy(priority);
}

void schedule()//invokes the scheduler
{
	int i;
	for(i = MAX_PRIORITY; i >= MIN_PRIORITY; --i)
	{
		if(head[i])
			scheduleP(i);
	}
	free(head);
	free(tail);
}


















