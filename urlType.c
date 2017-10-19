#include <stdio.h>
#include <stdlib.h>
#include "urlType.h"
#include <string.h>
#include <assert.h>

// Data structures
typedef struct url {
    char* urlN;
    int nWords;
    double PRVal;
    struct url *next;
    int printed;
} url;

typedef struct urlRep {
    struct url *first;
    int nUrls;
} urlRep;



// Helper functions
// Create url rep
urlRep *urlRepCreate() {
    urlRep *new = malloc(sizeof(urlRep));
    assert(new);
    new->first = NULL;
    new->nUrls = 0;
    return new;
}


// Insert a url
void insertURL(urlRep *U, char *urlN) {
    assert(U);

    // Check not already in set
    if (U->first != NULL) {
        for (url *curr = U->first; curr != NULL; curr = curr->next) {
            if (strcmp(urlN, curr->urlN) == 0) {
                //printf("Can't add url already in set.\n");
                return;
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
            printf("%s(%d)(%.7lf) ==> ", curr->urlN, curr->nWords, curr->PRVal);
        }
        printf("X\n");
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