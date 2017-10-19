#include <stdio.h>
#include <stdlib.h>


int findN(char*);

int main(argc, char *argv[]) {
    
    int N = findN("collection.txt"); // N in idf equation
    
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