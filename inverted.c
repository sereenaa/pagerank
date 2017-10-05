// Gets an index of words with each url that contains the word 
// Puts this in a linked list of words, where each node has a linked list of URLS 
// Outputs it into a txt file, with words sorted in alphabetical order and URLS sorted in ascending order 
// Written by Jesse Colville and Serena Xu 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "graph.h"
#include "queue.h"
#include "readData.h"
#include "assert.h"

#define MAX_WORD_SIZE 100

// Data struct for list of a list to represent which urls words are contained in
typedef struct lListRep {
	struct key *first;
	int nElems;
} lListRep;

typedef struct key {
	char word[MAX_WORD_SIZE];
	struct urlNode *urls;
	struct key *next;
} key;

typedef struct urlNode {
	char url[MAXURL];
	struct urlNode *next;
} urlNode;


int main(void) {

	FILE *fp; 
	char urlIn[MAXURL] = {0};
	char urlInTxt[MAXURL] = {0};
	char word[50] = {0}; 

	// Get set of urls
	Set urls = getCollection("collection.txt");

	// For each URL in set urls, make list of URLS for each word 
	for (int i=0; i<nElems(urls); i++) {

		// Open URL txt file 	
		strcpy(urlIn, getNth(urls, i));
		strcpy(urlInTxt, getNth(urls, i));
		strcat(urlInTxt, ".txt");
		fp = fopen(urlInTxt, "r");
		if (fp == NULL) {
			printf("Couldn't open file.\n");
			exit(1);
		}
		// Scan for words
		int ii = 0; 
		fscanf(fp, "s", word); 
		if (strcmp(word, "Section-2") == 1) {
			// For each word 
			while (strcmp(word, "#end") != 0) {
				// Remove spaces before/after word 
				// Convert all characters to lower case 
				// Remove punctuation marks (dot, comma, semicolon, question mark) 
				// Put each word into list 
				// Put URL with each word if not already there 
			} 
		} 
	} 

	// Output to txt file in alphabetical order 

	return 0;
}

// Helper functions
// Create a new list of a list
lListRep *createLList() {
	lListRep *new = malloc(sizeof(lListRep));
	if (new == NULL) {
		fprintf(stderr, "Malloc failed: Couldn't create lListRep.\n");
		exit(1);
	}
	return new;
}

// Add a word to the list (treat as a set)
void addWord(lListRep *L, char w[MAX_WORD_SIZE]) {
	assert(L);
	if (findWord(L, w)) return; 
	key *new = malloc(sizeof(key));
	if (new == NULL) {
		fprintf(stderr, "Malloc failed: Couldn't create key.\n");
		exit(1);
	}
	strcpy(new->word, w);
	new->urls == NULL;
	new->next == NULL;
	if (L->first == NULL) {
		L->first = new;
		return;
	}
	key *curr = L->first;
	for (curr = L->first; curr->next != NULL; curr = curr->next) /* Iterate to end of list*/;
	curr->next = new;
	return;
}

// Linear search for list for word
int findWord(lListRep *L, char *w) {
	assert(L);
	key *curr = L->first;
	for (curr = L->first; curr = curr->next; curr != NULL) {
		if (strcmp(curr->word, w) == 0) return 1;
	}
	return 0;
}

// Add a url to key
void addURL(lListRep *L, char word[MAX_WORD_SIZE], char url[MAXURL]) {
	assert(L);
	// Get to key
	key *curr = L->first;
	while (1) {
		if (curr == NULL) {
			printf("Word not in set. Unable to add URL.\n");
			return;
		}
		if (strcmp(curr->word, word) == 0) {
			break;
		} else { 
			curr = curr->next;
		}
	}
	// Check url not already in set
	if (findURL(curr, url)) return;
	// Malloc url
	urlNode *new = malloc(sizeof(urlNode));
	if (new == NULL ) {
		fprintf(stderr, "Couldn't malloc urlNode.\n");
		exit(1);
	}
	strcpy(new->url, url);
	new->next == NULL;
	// Append
	urlNode *currURL = curr->urls;
	if (currURL == NULL) {
		curr->urls = new;
		return;
	}
	for (currURL = curr; currURL->next != NULL; currURL = currURL->next) /*Iterate through list*/;
	currURL->next = new;
	return;

}

// Linear search of key for url
int findURL(key *k, char *url) {
	assert(k);
	urlNode *curr = k;
	for (curr = k; curr = curr->next; curr != NULL) {
		if (strcmp(curr->url, url) == 0) return 1;
	}
	return 0;
}