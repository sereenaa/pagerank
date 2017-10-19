#include <stdio.h>
#include <stdlib.h>
#define MAXURL 20


int findN(char*);

int abc(int argc, char *argv[]) {

    // Check there is a word to search for
    if (argc < 2) {
        printf("Not enough args.\n");
        exit(1);
    }



    int N = findN("collection.txt"); // N in idf equation
    printf("N = %d\n", N);
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