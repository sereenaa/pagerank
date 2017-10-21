// Gets an index of words with each url that contains the word
// Puts this in a linked list of words, where each node has a linked list of URLS
// Outputs it into a txt file, with words sorted in alphabetical order and URLS sorted in ascending order
// Written by Jesse Colville and Serena Xu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "set.h"
#include "graph.h"
#include "queue.h"
#include "readData.h"
#include "assert.h"
#include <unistd.h>
#include "keyType.h"


int main(void) {
	FILE *fp;
	char *urlIn = malloc(sizeof(char)*100);
	char *urlInTxt = malloc(sizeof(char)*100);
	char *word = malloc(sizeof(char)*100);

	// Get set of urls
	Set urls = getCollection("collection.txt");
	if (isEmpty(urls)) return 1;

	// Create list rep
	lListRep *L = createLList();

	// For each URL in set urls, make list of URLS for each word
	for (int i=0; i<nElems(urls); i++) {
		strcpy(urlIn, getNth(urls, i));
		strcpy(urlInTxt, getNth(urls, i));
		strcat(urlInTxt, ".txt");
		fp = fopen(urlInTxt, "r");
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

	printInverted(L);
	return 0;
}
