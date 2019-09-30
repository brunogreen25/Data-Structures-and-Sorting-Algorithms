#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 14
#define M 8

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

//returns the first constant for address evaluation
int address_one(int key) {
	return key%M;
}

//returns the second constant for address evaluation
int address_two(int key) {
	return 1 + key % (M - 1);
}

//adds the element to the hash table
void enter(struct entry* hash, int name, int key) {
	int index;
	int h1 = address_one(key);
	int h2 = address_two(key);

	struct entry element;
	strcpy(element.name, name);
	element.key = key;

	for (int i = 0; i<M; i++) {
		index = (int)fmod((h1 + i*h2), M);
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