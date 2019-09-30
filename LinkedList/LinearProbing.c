#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH
#define M 7

struct entry {
	int key;
	char name[NAME_LENGTH + 1];
};

//deletes the n elements from the hash table
void empty(struct entry* hash, int n) {
	for (int i = 0; i<n; i++) {
		hash[i].key = 0;
		*hash[i].name = '\0';
	}
}

//returns the constant for address evaluation
int address(int key) {
	int sum = 0;
	char arr[2] = { 0 };

	for (int i = 0; i<3; i++) { //overlaping method, only the middle part remains not inverted
		if (i != 1) {
			arr[0] = key % 10;
			key = key / 10;
			arr[1] = key % 10;
			key = key / 10;
			sum += arr[0] * 10 + arr[1];
		}
		else {
			arr[0] = key % 10;
			key = key / 10;
			arr[1] = key % 10;
			key = key / 10;
			sum += arr[1] * 10 + arr[0];
		}
	}

	return sum;
}

//adds the new element to the hash table
void enter(struct entry* hash, int name, int key) {
	int index;
	int _address = address(key);

	struct entry element;
	strcpy(element.name, name);
	element.key = key;

	for (int i = 0; i<M; i++) {
		index = (_address + i) % M;
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