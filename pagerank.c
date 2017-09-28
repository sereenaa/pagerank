// Written by Jesse Colville
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "graph.h"
#include "set.h"
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
typedef dataListRep *dataList;

dataList calculatePageRank(Graph, Set, double, double, int);
dataList createDataList();
dataList copyDataList(dataList);
void insertDataListNode(dataList L, char *key, int degrees, double PRVal);
void showDataList(dataList L);
double calcPROthers(dataList, Node *);

int main(int argc, char *argv[]) {
	// Get arguments
	if (argc != 4) {
		fprintf(stderr, "Incorrect number of arguments.\n");
		exit(1);
	}
	double d = atof(argv[1]);
	double diffPR = atof(argv[2]);
	int maxIt = atoi(argv[3]);
	
	// Get set of urls and create and initialise the graph
	Set urls = getCollection("collection.txt");
	Graph g = getGraph(urls);

	// Calculate pagerank
	dataList L = calculatePageRank(g, urls, d, diffPR, maxIt);


	return 0;
}

dataList calculatePageRank(Graph g, Set urls, double d, double diffPR, int maxIt) {
	assert(g);
	nPages = nElems(urls);
	// Create an empty list
	dataList newL = createDataList();

	// Initialise list with url, degrees, and PRValue to 1/numberURLS
	int i;
	for (i = 0; i < nElems(urls); i++) {
		insertDataListNode(newL, getNth(urls, i), nEdgesV(g, getNth(urls, i)), 1.0/nPages);
	}

	// Copy the list which will as we need to keep track of prev iteration
	dataList prevL = copyDataList(newL);


	i = 0;
	double diff = diffPR;
	Node *curr = newL->first;

	while (i < maxIt && diff >= diffPR) {
		i++;
		// For each page
		for (curr = newL->first; curr != NULL; curr = curr->next) {
			curr->PRVal = (1.0 - d)/nPages + d*calcPROthers(prevL, curr->key);
		}
		prevL = copyDataList(newL);
	}
}

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

dataList copyDataList(dataList L) {
	assert(L);
	// Create list
	dataListRep *new = malloc(sizeof(dataListRep));
	assert(new != NULL);
	new->nElems = 0;
	new->first = NULL;

	// Copy nodes
	Node *curr = L->first;
	while(curr != NULL) {
		insertDataListNode(new, curr->key, curr->degrees, curr->PRVal);
		curr = curr->next;
	}
	return new;
}

// Calculates the "second half" of the page rank formula
double calcPROthers(dataList L, char *skip) {
	assert(L);
	Node *curr = L->first;
	double sum = 0;
	double wIn = 0;
	double wOut = 0;
	for (curr; curr != NULL; curr = curr->next) {
		if (strcmp(curr->key, skip) == 0) continue;
	}
	return sum;
}