// Written by Jesse Colville
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "graph.h"
#include "set.h"
#include "readData.h"
#include "assert.h"

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
double calcPROthers(dataList, Graph, Node *);
void myRevBubble(dataList);

int pagerank(int argc, char *argv[]) {
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
	showGraph(g, 1);

	// Calculate pagerank
	dataList L = calculatePageRank(g, urls, d, diffPR, maxIt);
	myRevBubble(L);
	showDataList(L);

	// Print to pagerankList.txt
	FILE *fp = fopen("pagerankList.txt", "w");
	if (fp == NULL) {
		fprintf(stderr, "Could not open pagerankList.txt for writing.\n");
		exit(1);
	}
	Node *curr = L->first;
	for (curr = L->first; curr != NULL; curr = curr->next) {
		fprintf(fp, "%s, %d, %lf\n", curr->key, curr->degrees, curr->PRVal);
	}
	fclose(fp);

	return 0;
}

dataList calculatePageRank(Graph g, Set urls, double d, double diffPR, int maxIt) {
	assert(g);
	int nPages = nElems(urls);
	// Create an empty list
	dataList newL = createDataList();

	// Initialise list with url, degrees, and PRValue to 1/numberURLS
	int i;
	for (i = 0; i < nElems(urls); i++) {
		insertDataListNode(newL, getNth(urls, i), nEdgesOutV(g, getNth(urls, i)), 1.0/nPages);
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
			curr->PRVal = (1.0 - d)/nPages + d*calcPROthers(prevL, g, curr);
		}
		prevL = copyDataList(newL);
	}
	return newL;
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
	if (curr == NULL) {
		printf("Empty list.\n");
		return;
	}
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
double calcPROthers(dataList L, Graph g, Node *n) {
	assert(L);
	Node *curr = L->first;
	double sum = 0;
	double wIn = 0;
	double wOut = 0;
	int wInDenom = incomingFromOutgoing(g, n->key);
	int wOutDenom = outgoingFromOutgoing(g, n->key);
	for (curr = L->first; curr != NULL; curr = curr->next) {
		if (isConnectedOut(g, n->key, curr->key)) {
			wIn = nEdgesInV(g, curr->key) * 1.0 / wInDenom;
			if (wOutDenom == 0) {
				wOut = 0.5;
			} else {
				wOut = nEdgesOutV(g, curr->key) * 1.0 / wOutDenom;
			}
			sum += 1.0 * curr->PRVal * wIn * wOut;
			//printf("n = %s, curr = %s\nnedgesinv = %d nedgesoutv = %d\nwInDen = %d wOutDenom = %d\nwin = %lf wout = %lf\nsum = %lf\n\n",n->key,curr->key,nEdgesInV(g, curr->key), nEdgesOutV(g, curr->key), wInDenom, wOutDenom,wIn, wOut, sum);
		}
	}
	return sum;
}

// Bubble sort dataList in descending order
void myRevBubble(dataList L) {
	Node *head = L->first;
	Node *n = head;
	char tempKey[20];
	double tempPR = 0;
	int tempDeg = 0;
	if (head == NULL || head->next == NULL) return;
	int swapped = 1;
	while (swapped) {
		swapped = 0;
		for (n = L->first; n->next != NULL; n = n->next) {
			if (n->PRVal < n->next->PRVal) {
				// Switch data
				strcpy(tempKey, n->key);
				strcpy(n->key, n->next->key);
				strcpy(n->next->key, tempKey);
				tempPR = n->PRVal;
				n->PRVal = n->next->PRVal;
				n->next->PRVal = tempPR;
				tempDeg = n->degrees;
				n->degrees = n->next->degrees;
				n->next->degrees = tempDeg;

				swapped = 1;
			}
		}
	}
}