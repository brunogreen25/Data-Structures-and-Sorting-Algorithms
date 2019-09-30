#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 10

#define NAME_LENGTH 256
#define M 8

struct node {
    char name[NAME_LENGTH + 1];
    struct node* next;
};

//evaluates the address to save the values
int address(char *name) {
    int ascii_value = 0;
    
    for (int i=0;i<strlen(name);i++) {
        ascii_value += (int)name[i];
    }
    
    return ascii_value % M;
}

//deletes all elements from the list
void clear(struct node *hash[], int n) {
    for (int i=0;i<n;i++) {
        hash[i]=NULL;
    }
}

//adds the new element to hash table
void enter(struct node* hash[], char *new_name) {
    struct node* element = (struct node*)malloc(sizeof(struct node));
    strcpy(element -> name, new_name);
    
    int i = address(element->name);
    element->next=hash[i];
    hash[i]=element;
}

//returns the element of the hash table
struct node* get(struct node *hash[], char *new_name) {
    struct node *head;
    int i = address(new_name);
    
    for (head = hash[i];head && strcmp(head->name, new_name); head=head->next);
    
    return head;
}

//prints the hash table
void print_table(struct node* hash[]) {
    struct node *tmp;
    for(int i=0;i<M;i++) {
        tmp=hash[i];
        printf("%d ", i);
        while(tmp!=NULL) {
            printf(" %s", tmp->name);
            tmp=tmp->next;
        }
        printf("\n");
    }
}