// Jesse Colville
#include <stdio.h>
#include <stdlib.h>
#include "urlType.h"
#include "string.h"
#define MAXURL 20


int findN(char*);

int p2(int argc, char *argv[]) {

    // Check there is at least one word to search for
    if (argc < 2) {
        printf("Not enough args.\n");
        exit(1);
    }
    // Change args to lower case
    lowerArgs(argc, argv);
    // Declare url set
    urlRep *U = urlRepCreate();

    // Open invertedIndex
    FILE *fp;
    fp = fopen("invertedIndex.txt", "r");
    if (fp == NULL) {
        printf("Could not read file.\n");
        exit(1);
    }
    char urlN[MAXURL];
    char word[BUFFSIZE];
    char *tk;
    char line[BUFFSIZE];
    int idfDenom;
    int added;
    // Scan through inverted index looking for urls with target word(s)
    // When word is found, modify the tf values for each url containing 
    // that word
    while (fgets(line, BUFFSIZE, fp)) {
        tk = strtok(line," ,");
        if (isMemberArg(argv, tk, argc)) {
            strcpy(word, tk);
            tk = strtok(NULL," ,");
            while (tk != NULL) {
                added = insertURL(U, tk);
                if (added) idfDenom++;
                strcpy(urlN, tk);
                modTf(U, urlN, word);
                tk = strtok(NULL," ,'\n'");
            }
        }
    }
    fclose(fp);

    int N = findN("collection.txt"); // N in idf equation
    calcTfIdf(U, N, idfDenom);
    showUrls(U);
    return 0;
}

// Find total number of Documents
// N in idf equation
int findN(char *collection) {
    int N = 0;
    FILE *fp;
    fp = fopen(collection, "r");
    if (fp == NULL) {
        printf("Could not read file.\n");
        exit(1);
    }

    char URL[MAXURL];
    while (fscanf(fp, "%s", URL) != EOF) {
        N++;
    }
    fclose(fp);

    return N;
}