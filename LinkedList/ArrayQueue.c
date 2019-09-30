#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10

typedef struct {
	int data[MAX_LENGTH];
	int front, rear;
} Queue;

//initializes queue
void init_queue(Queue *queue) {
	queue->front = queue->rear = 0;
}

//returns true if the queue is empty
int is_empty(Queue queue) {
	return queue.rear == queue.front ? 1 : 0;
}

//returns true if the queue is full
int is_full(Queue queue) {
	return (queue.rear + 1) % MAX_LENGTH == queue.front;
}

//returns true if the value is in the queue
int contains(Queue queue, int val) {
	if (is_empty(queue))
		return 0;

	do {
		if (queue.data[++queue.front] == val)
			return 1;
	} while (queue.front < queue.rear);

	return 0;
}

//prints the elements of the queue
int print_queue(Queue queue) {
	if (is_empty(queue))
		return 0;

	do {
		printf("%d ", queue.data[++queue.front]);
	} while (queue.front < queue.rear);

	return 1;
}

//returns the size of the queue
int size(Queue queue) {
	return queue.rear - queue.front;
}

//adds the element to the queue
int add(Queue *queue, int val) {
	if (is_full(*queue))
		return 0;

	queue->rear++;
	queue->rear %= MAX_LENGTH;
	queue->data[queue->rear] = val;

	return 1;
}

//poll function: returns and removes the element from the queue
int poll(Queue *queue, int *val) {
	if (is_empty(*queue))
		return 0;

	queue->front++;
	queue->front %= MAX_LENGTH;
	*val = queue->data[queue->front];

	return 1;
}

//peek function: returns the element from the queue without removing it
int peek(Queue queue, int *val) {
	if (is_empty(queue))
		return 0;

	*val = queue.data[--queue.rear];

	return 1;
}

//main function (for testing)
int main()
{
	Queue queue;
	int a = NULL;

	init_queue(&queue);

	printf("--%d ", size(queue));

	add(&queue, 3);
	add(&queue, 5);
	peek(queue, &a);
	add(&queue, 7);
	add(&queue, 1);

	print_queue(queue);

	printf("--%d ", size(queue));

	return 0;
}