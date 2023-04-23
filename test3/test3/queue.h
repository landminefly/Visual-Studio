#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct QueueNode {
	int value;
	struct QueueNode* next;
} QueueNode, * List;

typedef struct Queue {
	QueueNode* rear;
}*Queue;

Queue initQueue();

void clear(Queue q);

int isEmpty(Queue q);

void enQueue(Queue q, int value);

int deQueue(Queue q);