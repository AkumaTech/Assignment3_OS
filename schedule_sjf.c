/*
Shortest job first
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

struct node* head = NULL;
struct node* tail;

void destroy()//destroys the list memory
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

Task* newTask(char* name, int priority, int burst)//creates new task
{
	Task* n_task = (Task*)malloc(sizeof(Task));
	n_task->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
	strcpy(n_task->name, name);
	n_task->priority = priority;
	n_task->burst = burst;
	n_task->tid = 0;
	return n_task;
}

void add(char* name, int priority, int burst)//adds the task to the list
{
	if(head == NULL)
	{
		head = (struct node*)malloc(sizeof(struct node));
		head->next = NULL;
		head->task = NULL;
		tail = head;
	}
	struct node* curr;
	struct node* pre;
	pre = head;
	curr = head->next;
	while(curr)
	{
		if(burst >= curr->task->burst)
		{
			pre = curr;
			curr = curr->next;
		}
		else
			break;
	}
	pre->next = (struct node*)malloc(sizeof(struct node));
	pre = pre->next;
	pre->next = curr;
	pre->task = newTask(name, priority, burst);
}

void schedule()//invokes the scheduler 
{
	struct node* p = head->next;
	while(p)
	{
		run(p->task, p->task->burst);
		p = p->next;
	}
	destroy();
}
