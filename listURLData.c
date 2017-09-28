// Jesse Colville September 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listURLData.h"
#include "assert.h"
#define MAXURL 20

typedef struct Node {
	char key[MAXURL];
	int degrees;
	double PRVal;
	struct Node *next;
} Node;

typedef struct dataListRep {
	int nElems;
	Node *first;
} dataListRep;


// Create an empty list
dataList createDataList() {
	dataListRep *new = malloc(sizeof(dataListRep));
	assert(new != NULL);
	new->nElems = 0;
	new->first = NULL;
	return new;
}

// Insert a node into the list
void insertDataListNode(dataList L, char *key, int degrees, double PRVal) {
	assert(L);
	// Initialise node
	Node *n = malloc(sizeof(Node));
	assert(n != NULL);
	strcpy(n->key, key);
	n->degrees = degrees;
	n->PRVal = PRVal;
	n->next = NULL;

	// Add to list
	if (L->nElems == 0) {
		L->first = n;
	} else {
		Node *curr = L->first;
		while (curr->next != NULL) curr = curr->next;
		curr->next = n;
	}
	L->nElems++;
}

void showDataList(dataList L) {
	assert(L);
	Node *curr = L->first;
	while (curr != NULL) {
		printf("%s, %d, %lf\n", curr->key, curr->degrees, curr->PRVal);
		curr = curr->next;
	}
}