#include <stdio.h>
#include <string.h>

typedef struct _node {
	int data;
	struct _node *next;
} node;

//initializes the list
void init(node** head_ref)
{
	*head_ref = NULL;
}

//searches list with the value val and returns the node with that value
node* search(node* head, int val) {
	node *p = head;
	do {
		if (p->data == val)
			return p;
	} while (p = p->next);
	return NULL;
}

//returns true if the value is in the linked list
int contains(node *head, int val) {
	node *p = head;
	do {
		if (p->data == val)
			return 1;
	} while (p = p->next);
	return 0;
}

//prints list on console
int print_list(node* head)
{
	if (head == NULL)
		return -1;

	do {
		printf("%d ", head->data);
	} while (head = head->next);
	return 0;
}

//appends the value to the list
int append(node** head_ref, int val)
{
	node *new_node, *p;
	if ((new_node = (node*)malloc(sizeof(node))) == NULL)
		return -1;

	new_node->data = val;
	new_node->next = NULL;

	if (*head_ref != NULL) {
		for (p = *head_ref; p->next; p = p->next);
		p->next = new_node;
	}
	else
		*head_ref = new_node;

	return 0;
}

//removes the element from the list with the value val
int remove_by_value(node** head_ref, int val)
{
	node* p;

	for (; *head_ref && (*head_ref)->data != val; head_ref = &((*head_ref)->next));

	if (*head_ref)
	{
		p = *head_ref;
		*head_ref = (*head_ref)->next;
		free(p);
		return 0;
	}
	
	return -1;
}

//removes the i-th element from the list
int remove_by_index(node** head_ref, int i)
{
	node* p;

	for (; *head_ref && (i--) > 0; head_ref = &((*head_ref)->next));

	if (*head_ref)
	{
		p = *head_ref;
		*head_ref = (*head_ref)->next;
		free(p);
		return 0;
	}

	return -1;
}

//removes the last element from the list
int remove_last(node **head_ref)
{
	if (*head_ref == NULL)
		return -1;

	if ((*head_ref)->next == NULL)
	{
		*head_ref = NULL;
		return 0;
	}

	while ((*head_ref)->next->next != NULL)
		head_ref = &((*head_ref)->next);

	free((*head_ref)->next);
	(*head_ref)->next = NULL;

	return 0;
}

//removes all elements from list
int remove_all(node **head_ref)
{
	node *p = *head_ref;

	if (*head_ref == NULL)
		return -1;

	while (*head_ref)
	{
		p = *head_ref;
		*head_ref = (*head_ref)->next;
		free(p);
	}
	
	return 0;
}

//merges the second list to the first one
int merge_lists(node **head_ref1, node *head_ref2)
{
	while (head_ref2 != NULL)
	{
		append(head_ref1, head_ref2->data);
		head_ref2 = head_ref2->next;
	}
}

//returns the size of the list
int size(node *head)
{
	int n = 0;

	if (head != NULL)
	{
		do {
			n++;
		} while ((head = head->next) != NULL);
	}

	return n;
}

//swaps the two nodes
void swap(node *q1, node *q2) {
	node *temp = q2->next;
	q2->next = q1;
	q1->next = temp;
}

int list_bubble_sort_imporved(node **head) {
	node **h;
	int swapped, count = 0;

	for (node* q = *head; q != NULL; q = q->next) {
		count++;
	}

	for (int i = 0; i <= count; i++) {
		h = head;
		swapped = 0;
		for (int j = 0; j < count - i - 1; j++) {
			node *p1 = *h;
			node *p2 = p1->next;
			if (p1->data > p2->data) {
				swap(p1, p2);
				*h = p2;
				swapped = 1;
			}
			h = &(*h)->next;
		}

		if (swapped == 0)
			break;
	}
}

//makes the union of the first two parameters (which are linked lists) and stores it to the third parameter(which is also a list)
int list_union(node *head1, node *head2, node **head_res)
{
	list_bubble_sort_improved(&head1);
	list_bubble_sort_improved(&head2);

	if (head1 == NULL && head2 == NULL) return -1;

	//add elements of the first list
	while (head1 != NULL)
	{
		if(append(head_res, head1->data) == -1)
			return -1;
		head1 = head1->next;
	}

	//add the elements of the second list which were not already added
	while (head2 != NULL)
	{
		if (contains(*head_res, head2->data) == 0) {
			if (append(head_res, head2->data) == -1)
				return -1;
		}
		head2 = head2->next;
	}

	list_bubble_sort(&head_res);
	return 0;
}

//makes the intersection of the first and second parameters (which are linked lists) and stores it in the third parameter
int list_intersection(node *head1, node *head2, node **head_res)
{
	list_bubble_sort_imporved(&head1);
	list_bubble_sort_imporved(&head2);

	//copies the element only if it is contained in both lists
	while (head1 != NULL && head2 != NULL)
	{
		if (head1->data > head2->data)
			head2 = head2->next;
		else if (head1->data < head2->data)
			head1 = head1->next;
		else
		{
			if (append(head_res, head1->data) == -1)
				return -1;

			head1 = head1->next;
			head2 = head2->next;
		}
	}
	return 0;
} 


//main function (for testing)
int main()
{
	node *head;

	init(&head);

	append(&head, 3);
	remove_all(&head);

	append(&head, 2);
	append(&head, 4);
	append(&head, 1);
	append(&head, 8);
	remove_last(&head);

	append(&head, 9);

	print_list(head);

	remove_by_index(&head, 3);
	print_list(head);

	remove_all(&head);
	printf("--%d--", size(head));



	system("pause");
	return 0;
}