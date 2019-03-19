/*
Round robin
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

struct node* head = NULL;
struct node* tail;

void destroy()//deletes the memory in a list
{
	tail = head;
	head = head->next;
	free(tail);
	while(head)
	{
		tail = head;
		head = head->next;
		free(tail->task->name);
		free(tail->task);
		free(tail);
	}
}

void removeNode(struct node* n)//destroys a nodes information
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
	if(head == NULL)
	{
		head = (struct node*)malloc(sizeof(struct node));
		head->next = NULL;
		head->task = NULL;
		tail = head;
	}
	tail->next = (struct node*)malloc(sizeof(struct node));
	tail = tail->next;
	tail->task = newTask(name, priority, burst);
	tail->next = NULL;
}

void schedule()//invokes the scheduler
{
	int s;
	struct node* tp;
	while(head->next)
	{
		s = (TIME < head->next->task->burst)?TIME:head->next->task->burst;
		run(head->next->task, s);
		if(head->next->task->burst == s)
		{
			tp = head->next;
			head->next = head->next->next;
			removeNode(tp);
		}
		else
		{
		head->next->task->burst -= s;
		tail->next = head->next;
		tail = tail->next;
		head->next = head->next->next;
		tail->next = NULL;
		}
	}
	destroy();
}
