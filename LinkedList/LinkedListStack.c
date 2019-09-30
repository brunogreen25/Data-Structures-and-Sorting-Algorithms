#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

typedef struct node Node;

typedef struct {
	Node *top;
} Stack;

//initializes the stack
void init_stack(Stack *stack) {
	stack->top = NULL;
}

//returns true if the stack is empty
int is_empty(Stack stack) {
	return stack.top == NULL ? 1 : 0;
}

//push function: adds the element to the stack
int push(Stack *stack, int val) {
	Node *temp;
	if ((temp = (Node*)malloc(sizeof(Node))) == NULL)
		return -1;

	temp->data = val;
	temp->next = stack->top;
	stack->top = temp;

	return 0;
}

//pop function: returns and removes the element from stack
int pop(Stack *stack, int *val) {
	Node *temp;
	if (is_empty(*stack))
		return -1;

	*val = stack->top->data;

	temp = stack->top;
	stack->top = stack->top->next;
	free(temp);
	return 0;
}

//peek function: returns the element from stack without removing it
int peek(Stack *stack, int *data) {
	if (pop(stack, data) == -1) {
		return -1;
	}
	else {
		push(stack, *data);
		return 0;
	}
}

//prints the elements from the stack
int print_stack(Stack stack) {
	if (is_empty(stack))
		return 0;

	do {
		printf("%d", (stack.top)->data);
	} while (stack.top = stack.top->next);
	return 1;
}

//returns true if the value is in the stack
int contains(Stack stack, int val) {
	if (is_empty(stack)) {
		return 0;
	}

	do {
		if (stack.top->data == val)
			return 1;
	} while (stack.top = stack.top->next);
	return 0;
}

//returns the size of the stack
int size(Stack stack) {

	int n = 0;

	if (!is_empty(stack)) {
		do {
			n++;
		} while (stack.top = stack.top->next);
	}
	return n;
}

//main function (for testing)
int main()
{
	Stack stack;
	init_stack(&stack);

	push(&stack, 3);
	push(&stack, 4);
	push(&stack, 5);
	push(&stack, 1);

	print_stack(stack);

	printf("%d", contains(stack, 54));
	printf("%d", size(stack));

	return 0;
}