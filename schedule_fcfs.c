/*
First come, first serve
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

void destroy()//to destroy the memory in the list
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

Task* newTask(char* name, int priority, int burst)//this creates a new task
{
	Task* n_task = (Task*)malloc(sizeof(Task));
	n_task->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
	strcpy(n_task->name, name);
	n_task->priority = priority;
	n_task->burst = burst;
	n_task->tid = 0;
	return n_task;
}

void add(char* name, int priority, int burst)//adds the tasks the list
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
	struct node* p = head->next;
	while(p)
	{
		run(p->task, p->task->burst);
		p = p->next;
	}
	destroy();
}










