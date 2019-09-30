#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct queue {
	struct node *front;
	struct node *rear;
};

typedef struct node Node;
typedef struct queue Queue;

//initializes queue's front and rear pointers
void init_queue(Queue *queue) {
	queue->front = NULL;
	queue->rear = NULL;
}

//returns true if the queue is empty
int is_empty(Queue queue) {
	return queue.front == NULL ? 1 : 0;
}

//returns true if the queue contains the value
int contains(Queue queue, int val) {
	if (is_empty(queue))
		return 0;

	do {
		if (queue.front->data == val)
			return 1;
	} while (queue.front = queue.front->next);
	return 0;
}

//prints queue
int print_queue(Queue queue) {
	if (is_empty(queue))
		return 0;

	do {
		printf("%d ", queue.front->data);
	} while (queue.front = queue.front->next);
	return 1;
}

//returns the size of the queue
int size(Queue queue) {
	int n = 0;

	if (!is_empty(queue)) {
		do {
			n++;
		} while (queue.front = queue.front->next);
	}

	return n;
}

//adds the element to queue
int add(Queue *queue, int val) {
	Node *temp;
	if ((temp = (Node*)malloc(sizeof(Node))) == NULL)
		return 0;

	temp->data = val;
	temp->next = NULL;

	if (queue->front == NULL) {
		queue->front = temp;
		queue->rear = temp;
	}
	else {
		queue->rear->next = temp;
		queue->rear = temp;
	}

	return 1;
}

//poll function: returns and removes the element from the queue
int poll(Queue *queue, int *val) {
	Node *temp;
	if (is_empty(*queue)) {
		return 0;
	}

	*val = queue->front->data;

	temp = queue->front;
	queue->front = queue->front->next;
	free(temp);

	if (is_empty(*queue)) {
		queue->rear = NULL;
	}

	return 1;
}

//peek function: returns the element from the queue without removing it
int peek(Queue queue, int *val) {
	if (is_empty(queue))
		return 0;

	*val = queue.front->data;

	return 1;
}

//main function (for testing)
int main()
{
	Queue queue;
	int a = 3;
	init_queue(&queue);

	printf("\n%d", size(queue));

	add(&queue, 3);
	add(&queue, 4);
	poll(&queue, &a);
	add(&queue, 5);
	add(&queue, 6);

	print_queue(queue);
	printf("\n%d", size(queue));

	return 0;
}