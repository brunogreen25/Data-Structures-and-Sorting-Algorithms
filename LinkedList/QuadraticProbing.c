#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH
#define M 8

#define c1 0.5
#define c2 0.5

struct entry {
	int key;
	char name[NAME_LENGTH + 1];
};

//deletes the n elements of the hash table
void empty(struct entry* hash, int n) {
	for (int i = 0; i<n; i++) {
		hash[i].key = 0;
		*hash[i].name = '\0';
	}
}

//returns the constant for address evaluation
unsigned long int address(int key) {
	unsigned int A = 2654435769; //constant A is chosen by the reccomended value for 32bit words (Knuth)
	unsigned int move = 29; // (word length) k = 32 - 3 (32 because the word is 32bit, and 3 because 2'3==8==M
	return (A*key) >> move;
}

//adds the element to hash table
void enter(struct entry* hash, int name, int key) {
	int index;
	unsigned long int _address = address(key);

	struct entry element;
	strcpy(element.name, name);
	element.key = key;

	for (int i = 0; i<M; i++) {
		index = (int)fmod((_address + c1*i + c2*i*i), M);
		if (hash[index].key == 0) {
			hash[index] = element;
			break;
		}
	}
}

//prints the hash table
void print_table(struct entry *hash) {
	for (int i = 0; i<M; i++)
		printf("%d %s", hash[i].key, hash[i].name);
}