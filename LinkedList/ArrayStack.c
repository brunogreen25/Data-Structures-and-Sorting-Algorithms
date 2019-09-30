#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10

typedef struct {
	int top, data[MAX_LENGTH];
} Stack;

//initializes stack index
void init_stack(Stack *stack) {
	stack->top = -1;
}

//returns true if stack is empty
int is_empty(Stack stack) {
	return stack.top < 0 ? 1 : 0;
}

//returns true is stack is full
int is_full(Stack stack) {
	return stack.top + 1 == MAX_LENGTH ? 1 : 0;
}

//returns the size of the stack
int size(Stack stack) {
	return stack.top + 1;
}

//returns true if the stack contains the value
int contains(Stack stack, int val) {
	if (is_empty(stack))
		return 0;

	do {
		if (stack.data[stack.top--] == val)
			return 1;
	} while (stack.top > 0);

	return 0;
}

//prints the values of the stack
int print_stack(Stack stack) {
	if (!is_empty(stack)) {

		do {
			printf("%d ", stack.data[stack.top--]);
		} while (stack.top >= 0);

	}

	return 0;
}

//push function: inserts the value in stack
int push(Stack *stack, int val) {
	if (stack->top >= MAX_LENGTH - 1)
		return 0;

	stack->top++;
	stack->data[stack->top] = val;
	return 1;
}

//pop function: returns and removes the value from the stack
int pop(Stack *stack, int *val) {
	if (stack->top < 0)
		return 0;

	*val = stack->data[stack->top];
	stack->top--;
	return 1;
}

//peek function: returns the value from the stack without removing it 
int peek(Stack *stack, int *val) {
	if (stack->top < 0)
		return 0;

	*val = stack->data[stack->top];
	return 1;
}

//main function (for testing)
int main()
{
	Stack stack;
	int a = 3;

	init_stack(&stack);

	push(&stack, 3);
	push(&stack, 4);
	push(&stack, 5);
	push(&stack, 1);
	pop(&stack, &a);

	printf("**%d", a);

	peek(&stack, &a);

	printf("**%d", a);

	print_stack(stack);

	printf("--%d", contains(stack, 5));
	printf("--%d", size(stack));

	return 0;
}