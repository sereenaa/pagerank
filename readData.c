// Written by Jesse Colville

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "graph.h"
#include "set.h"
#include "assert.h"

Set getCollection(char *);
Graph getGraph(Set);

int main(void) {

	// Read urls from collection.txt
	Set URLs = getCollection("Sample1/collection.txt");
	Graph g = getGraph(URLs);

	return 0;
}

// Function that takes in a file and returns a set with each string
Set getCollection(char *collection) {
	// Open file for reading
	FILE *fp;
	fp = fopen(collection, "r");
	if (fp == NULL) {
		printf("Could not read file.\n");
		exit(1);
	}

	// Create a set to store urls
	Set URLs = newSet();
	char URL[20] = {0};
	while (fscanf(fp, "%s", URL) != EOF) {
		insertInto(URLs, URL);
	}
	fclose(fp);

	return URLs;
}

// Function that takes a set of strings and returns a graph with edges between strings (Adjacency matrix)
Graph getGraph(Set urls) {
	assert(urls);
	Graph g = newGraph(nElems(urls));
	int i;
	// For each url in set
	for (i = 0; i < nElems(urls); i++) {
		
	}
	return g;
}