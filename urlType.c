// ADT for pagerank urls
// Jesse Colville and Serena Xu

#include <stdio.h>
#include <stdlib.h>
#include "urlType.h"
#include <string.h>
#include <assert.h>
#include <ctype.h>

// Data structures
typedef struct url {
    char* urlN;
    int nWords;
    double PRVal;
    struct url *next;
    int printed;
    double tf;
    double idf;
    double tfIdf;
} url;

typedef struct urlRep {
    struct url *first;
    int nUrls;
} urlRep;


// Create url rep
urlRep *urlRepCreate() {
    urlRep *new = malloc(sizeof(urlRep));
    assert(new);
    new->first = NULL;
    new->nUrls = 0;
    return new;
}


// Insert a url
int insertURL(urlRep *U, char *urlN) {
    assert(U);

    // Check not already in set
    if (U->first != NULL) {
        for (url *curr = U->first; curr != NULL; curr = curr->next) {
            if (strcmp(urlN, curr->urlN) == 0) {
                //printf("Can't add url already in set.\n");
                return 0;
            }
        }
    }

    // Allocate memory
    url *new = malloc(sizeof(url));
    assert(new);
    new->urlN = malloc(sizeof(strlen(urlN+1)));
    assert(new->urlN);

    // Set values
    strcpy(new->urlN, urlN);
    new->nWords = 0;
    new->next = NULL;
    new->printed = 0;
    new->tf = 0;
    new->idf = 0;
    new->tfIdf = 0;
    // Pagerank a bit more tricky to set
    FILE *fp;
    fp = fopen("pagerankList.txt", "r");
    if (fp == NULL) {
        printf("Could not read file.\n");
        exit(1);
    }
    char word[BUFFSIZE];
    char buf[BUFFSIZE];
    char PRVal[BUFFSIZE];
    char line[BUFFSIZE];
    while (fgets(line, BUFFSIZE, fp) != NULL) {
        sscanf(line, "%s %s %s", word, buf, PRVal);
        // Remove comma from word
        int i = 0;
        for (i = 0; word[i] != ','; i++) {
        }
        word[i] = '\0';
        if (strcmp(word, urlN) == 0) {
            new->PRVal = atof(PRVal);
            break;
        }
    }
    fclose(fp);

    // Append
    if (U->first == NULL) {
        U->first = new;
    } 
    else {
        url *curr = U->first;
        curr = findLast(curr);
        curr->next = new;
    }
    return 1;
}

// Helper function to append
url *findLast(url *url) {
    if (url->next == NULL) {
        return url;
    } 
    else {
        return findLast(url->next);
    }
}

void showUrls(urlRep *U) {
    assert(U);
    if (U->first == NULL) {
        printf("No urls.\n");
    }
    else {
        for (url *curr = U->first; curr != NULL; curr = curr->next) {
            printf("%s(nWords = %d)(PRVal = %.7lf)(tf-idf = %.6lf)\n", curr->urlN, curr->nWords, curr->PRVal, curr->tfIdf);
        }
    }
}

int isMemberArg(char **argv, char *word, int argc) {
    if (word == NULL) return 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], word) == 0) return 1;
    }
    return 0;
}

void countWord(urlRep *U, char* urlN) {
    assert(U);
    for (url *curr = U->first; curr != NULL; curr = curr->next) {
        if (strcmp(curr->urlN, urlN) == 0) {
            curr->nWords++;
            return;
        }
    }
    printf("Can't add word url not in set.\n");
}

void lowerArgs(int argc, char *argv[]) {
    for (int i = i; i < argc; i++) {
        for (int ii = 0; ii < strlen(argv[i]); ii++) {
            argv[i][ii] = tolower(argv[i][ii]);
        }
    }
}

void modTf(urlRep *U, char* urlN, char* target) {
    assert(U);

    // Open url
    char urlTxt[BUFFSIZE];
    strcpy(urlTxt, urlN);
    strcat(urlTxt, ".txt");
    FILE *fp;
    fp = fopen(urlTxt, "r");
    if (fp == NULL) {
        printf("Could not read file.\n");
        exit(1);
    }

    int sumTarg = 0;
    int sumTot = 0;
    char word[BUFFSIZE];
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
                sumTot++;
                if (strcmp(word, target) == 0) sumTarg++;
            }    
            break;
        }
    }
    // Moderate tf value at url
    url *curr;
    for (curr = U->first; strcmp(curr->urlN, urlN) != 0; curr = curr->next);
        // Iterate to url
    curr->tf += 1.0 * sumTarg / sumTot;
}

void calcTfIdf(urlRep *U, int N, int idfDenom) {
    assert(U);

    for (url *curr = U->first; curr != NULL; curr = curr->next) {
        curr->idf = 1.0 * N / idfDenom;
        curr->tfIdf = curr->tf / curr->idf;
    }
}