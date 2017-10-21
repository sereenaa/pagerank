// Jesse Colville
#include <stdio.h>
#include <stdlib.h>
#include "urlType.h"
#include "string.h"
#define MAXURL 20


int findN(char*);

int main(int argc, char *argv[]) {

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
        printf("Could not read invetedIndex.txt.\n");
        exit(1);
    }
    char urlN[MAXURL];
    char word[BUFFSIZE];
    char *tk;
    char line[BUFFSIZE];
    int idfDenom = 0;
    int added;
    // Scan through inverted index looking for urls with target word(s)
    // When word is found, modify the tf values for each url containing 
    // that word
    while (fgets(line, BUFFSIZE, fp)) {
        tk = strtok(line," ,\n");
        if (isMemberArg(argv, tk, argc)) {
            strcpy(word, tk);
            tk = strtok(NULL," ,\n");
            while (tk != NULL) {
                strcpy(urlN, tk);
                added = insertURL(U, urlN);
                if (added) idfDenom++;
                modTf(U, urlN, word);
                tk = strtok(NULL," ,\n");
            }
        }
    }
    fclose(fp);
    int N = findN("collection.txt"); // N in idf equation
    calcTfIdf(U, N, idfDenom);
    printPart2(U);
    return 0;
}

// Find total number of Documents
// N in idf equation
int findN(char *collection) {
    int N = 0;
    FILE *fp;
    fp = fopen(collection, "r");
    if (fp == NULL) {
        printf("Could not read collection.txt.\n");
        exit(1);
    }

    char URL[MAXURL];
    while (fscanf(fp, "%s", URL) != EOF) {
        N++;
    }
    fclose(fp);

    return N;
}