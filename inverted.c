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


// Data struct for list of a list to represent which urls words are contained in
typedef struct lListRep {
	struct key *first;
	int nWords;
} lListRep;

typedef struct key {
	char *word;
	int nUrls;
	struct urlNode *urls;
	struct key *next;
} key;

typedef struct urlNode {
	char *url;
	struct urlNode *next;
} urlNode;

lListRep *createLList();
void addWord(lListRep *, char *);
int findWord(lListRep *, char *);
void addURL(lListRep *, char *, char *);
int findURL(key *, char *);
void showlListRep(lListRep *);


int inverted(void) {

	FILE *fp; 
	char *urlIn = {0};
	char *urlInTxt = {0};
	char *word = {0}; 

	// Get set of urls
	Set urls = getCollection("collection.txt");

	// Create list rep
	lListRep *L = createLList();

	addWord(L, "word 1");
	if (L->first == NULL) return 0;
	addWord(L, "word 1");
	addWord(L, "word 2");
	addURL(L, "word 1", "url1");
	addURL(L, "word 1", "url1");
	addURL(L, "word 1", "url2");
	showlListRep(L);
	
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
		fscanf(fp, "%s", word); 
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
	new->first = NULL;
	new->nWords = 0;
	return new;
}

// Add a word to the list (treat as a set)
void addWord(lListRep *L, char *w) {
	assert(L);
	if (findWord(L, w)) return;
	key *new = malloc(sizeof(key));
	new->word = malloc(strlen(w+1));
	if (new == NULL || new->word == NULL) {
		fprintf(stderr, "Malloc failed: Couldn't create key.\n");
		exit(1);
	}
	L->nWords++;
	strcpy(new->word, w);
	new->urls = NULL;
	new->next = NULL;
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
	if (L->first == NULL) return 0;
	for (key *curr = L->first; curr != NULL; curr = curr->next) {
		if (strcmp(curr->word, w) == 0) return 1;
	}
	return 0;
}

// Add a url to key
void addURL(lListRep *L, char *word, char *url) {
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
	new->url = malloc(strlen(url+1));
	if (new == NULL || new->url == NULL) {
		fprintf(stderr, "Couldn't malloc urlNode.\n");
		exit(1);
	}
	strcpy(new->url, url);
	new->next = NULL;
	// Append
	urlNode *currURL = curr->urls;
	if (currURL == NULL) {
		curr->urls = new;
		curr->nUrls = 1;
		return;
	}
	for (currURL = curr->urls; currURL->next != NULL; currURL = currURL->next) /*Iterate through list*/;
	currURL->next = new;
	curr->nUrls++;
	return;

}

// Linear search of key for url
int findURL(key *k, char *url) {
	assert(k);
	if (k->urls == NULL) return 0;
	urlNode *curr = k->urls;
	for (curr = k->urls; curr != NULL; curr = curr->next) {
		if (strcmp(curr->url, url) == 0) return 1;
	}
	return 0;
}

// Show the list
void showlListRep(lListRep *L) {
	assert(L);
	int bl = 0;
	for (key *k = L->first; k != NULL; k = k->next) {
		bl = 1;
		printf("%s ", k->word);
		for (urlNode *n = k->urls; n != NULL; n = n->next) {
			printf(" %s", n->url);
		}
		printf("\n");
	}
	if (bl == 0) printf("Empty list.\n");
	return;
}