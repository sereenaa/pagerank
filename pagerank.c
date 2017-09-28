#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "graph.h"
#include "set.h"
#include "assert.h"
#include "listURLData.h"

dataList calculatePageRank(Graph, Set, double, double, int);

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

	// Create an empty list
	dataList newL = createDataList();

	// Initialise list with url, degrees, and PRValue to 1/numberURLS
	int i;
	for (i = 0; i < nElems(urls); i++) {
		insertDataListNode(newL, getNth(urls, i), nEdgesV(g, getNth(urls, i)), 1.0/nElems(urls));
	}

	i = 0;
	double diff = diffPR;

	while (i < maxIt && diff >= diffPR) {
		
	}
	showDataList(newL);
}