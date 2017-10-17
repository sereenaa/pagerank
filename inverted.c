// Gets an index of words with each url that contains the word
// Puts this in a linked list of words, where each node has a linked list of URLS
// Outputs it into a txt file, with words sorted in alphabetical order and URLS sorted in ascending order
// Written by Jesse Colville and Serena Xu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //for using tolower
#include "set.h"
#include "graph.h"
#include "queue.h"
#include "readData.h"
#include "assert.h"
#include <unistd.h>


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
	int val;
	struct urlNode *next;
} urlNode;

lListRep *createLList();
void addWord(lListRep *, char *);
int findWord(lListRep *, char *);
void addURL(lListRep *, char *, char *);
int findURL(key *, char *);
void showlListRep(lListRep *);


int main(void) {
	FILE *fp;
	char *urlIn = malloc(sizeof(char)*100);
	char *urlInTxt = malloc(sizeof(char)*100);
	char *word = malloc(sizeof(char)*100);

	// Get set of urls
	Set urls = getCollection("collection.txt");

	// Create list rep
	lListRep *L = createLList();

	/*addWord(L, "worda");
	if (L->first == NULL) return 0;
	addWord(L, "worda");
	addWord(L, "wordb");
	addURL(L, "worda", "url1");
	addURL(L, "worda", "url2");
	printf("0\n");
	addURL(L, "wordb", "url1");
	showlListRep(L);*/

	// For each URL in set urls, make list of URLS for each word
	for (int i=0; i<nElems(urls); i++) {
		//printf("4\n");
		// Open URL txt file
		//printf("%s\n", getNth(urls, i));
		strcpy(urlIn, getNth(urls, i));
		//printf("%s\n", urlIn);
		//printf("3\n");
		strcpy(urlInTxt, getNth(urls, i));
		strcat(urlInTxt, ".txt");
		fp = fopen(urlInTxt, "r");
		//printf("%s\n", urlInTxt);
		if (fp == NULL) {
			printf("Couldn't open file.\n");
			exit(1);
		}
		// Scan for words
		while (1) {
			fscanf(fp, "%s", word);
			if (strcmp(word, "Section-2") == 0) {
				while (1) {
					fscanf(fp, "%s", word);
					if (strcmp(word, "#end") == 0) break;
					// For each word, convert to lower case, remove spaces & punctuation
					for (int i=0; word[i]!= '\0'; i++) {
						if (word[i] == ' ' || word[i] == '.' || word[i] == ',' || word[i] == ';' || word[i] == '?' ) {
							word[i] = '\0';
						}
						word[i] = tolower(word[i]);
					}
					// Add to set

					addWord(L, word);
					addURL(L, word, urlIn);
				}
				break;
			}
		}
	}
	// Prints to output file.
	FILE *outputStream;
	outputStream = fopen("invertedIndex.txt", "w");
	if (outputStream == NULL) {
		fprintf(stderr, "txt file creation failed\n");
	}
	int j = 0;
	for (key *k = L->first; k != NULL; k = k->next) {
		j = 1;
		fprintf(outputStream, "%s ", k->word);
		for (urlNode *n = k->urls; n != NULL; n = n->next) {
			fprintf(outputStream, " %s", n->url);
		}
		fprintf(outputStream,"\n");
	}
	if (j == 0) printf("Empty list.\n");
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
	//printf("%s", w);
	assert(L);
	if (findWord(L, w)) return;

	// makes a new pointer to a word
	key *new = malloc(sizeof(key));

	// makes a new array for the word in the newly made key
	//printf("length of word is %lu\n", strlen(w));
	new->word = malloc(strlen(w)+1);

	// tests that key and word creation succeeded
	if (new == NULL || new->word == NULL) {
		fprintf(stderr, "Malloc failed: Couldn't create key.\n");
		exit(1);
	}

	// increases the number of words in set by 1
	L->nWords++;
	// puts the new word into the array
	strcpy(new->word, w);

	// makes the word's url list empty
	new->urls = NULL;

	// makes the word's next pointer point to NULL
	new->next = NULL;

	// if the set is empty make the word the first word and return
	if (L->first == NULL) {
		L->first = new;
		return;
	}

	// if the word is not the first word
	// make a pointer, curr, point to the first word
	key *curr = L->first;
	key *prev = L->first;

	// iterate through list and insert word in alphabetical order
	while (1) {
		if (curr == NULL) {
			prev->next = new;
			break;
		}
		//printf("entered 1\n");
		// compare each character in both the word in the list and the word to be inserted
		if (strcmp(new->word, curr->word) > 0) { //new word is bigger than word in list
			prev = curr;
			curr = curr->next;
		}
		else {
			// insert before current word
			if (strcmp(curr->word, L->first->word) == 0)  { // Inserting at head
				new->next = curr;
				L->first = new;
			} 
			else if (prev->next != NULL) {
				prev->next = new;
				new->next = curr;
			}
			break;
		}
		//printf("success\n");
	}
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
			printf("Word (%s) not in set. Unable to add URL.\n", word);
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
	// Set values
	strcpy(new->url, url);
	new->next = NULL;
	char value[10];
	int a = 3;
	int i = 0;
	while (new->url[a] != '\0') {
		value[i] = new->url[a];
		a++;
		i++;
	}
	value[i] = '\0';
	new->val = atoi(value);
	// Sorted insert
	urlNode *currURL = curr->urls;
	if (currURL == NULL) {
		curr->urls = new;
		curr->nUrls = 1;
		return;
	}
	int exitFlag = 0;
	while (exitFlag == 0) {
		// Head
		if (curr->urls->val < new->val) {
			new->next = curr->urls;
			curr->urls = new;
			exitFlag = 1;
		}
		// Tail
		else if (currURL->next == NULL) {
			currURL->next = new;
			exitFlag = 1;
		}
		// Middle
		else if (currURL->next->val < new->val) {
			new->next = currURL->next;
			currURL->next = new;
			exitFlag = 1;
		}
		currURL = currURL->next;
	}
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
