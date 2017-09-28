// Written by Jesse Colville, September 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "graph.h"
#include "set.h"
#include "assert.h"
#define MAXURL 20

Set getCollection(char *);
Graph getGraph(Set);

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
	char URL[MAXURL] = {0};
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
	if (g == NULL) {
		exit(1);
	}
	int i;
	int ii;
	FILE *fp;
	char urlIn[MAXURL] = {0};
	char urlInTxt[MAXURL] = {0};
	char urlOut[MAXURL] = {0};
	// For each url in set
	for (i = 0; i < nElems(urls); i++) {
		// Read <url>.txt file and update outgoing links in graph adt
		strcpy(urlIn, getNth(urls, i));
		strcpy(urlInTxt, getNth(urls, i));
		strcat(urlInTxt, ".txt");
		fp = fopen(urlInTxt, "r");
		if (fp == NULL) {
			printf("Couldn't open file.\n");
			exit(1);
		}
		ii = 0;
		fscanf(fp, "%s", urlOut);
		while (strcmp(urlOut, "#end") != 0) {
			// Dont add first 2 lines (not urls)
			if (ii > 1) {
				if (addEdge(g, urlIn, urlOut) != 1) {
					printf("Couldn't add edge.\n");
					exit(1);
				}
			}
			ii++;
			fscanf(fp, "%s", urlOut);
		}
		fclose(fp);
	}
	return g;
}