// Jesse Colville, October 2017
#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "queue.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "urlType.h"

int seachPagerank(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Not enough args.\n");
        exit(1);
    }
    // Create url set
    urlRep *U = urlRepCreate();
    // Turn arguments into lowercase
    lowerArgs(argc, argv);
    
    // Get the nWords in each URL (dont add if 0)
    FILE *fp;
    fp = fopen("invertedIndex.txt", "r");
    if (fp == NULL) {
        printf("Could not read file.\n");
        exit(1);
    }
    char *tk;
    char line[BUFFSIZE];
    // Scan through inverted index looking for urls
    while (fgets(line, BUFFSIZE, fp)) {
        tk = strtok(line," ,");
        if (isMemberArg(argv, tk, argc)) {
            tk = strtok(NULL," ,");
            while (tk != NULL) {
                insertURL(U, tk);
                countWord(U, tk);
                tk = strtok(NULL," ,'\n'");
            }
        }
    }
    fclose(fp);
    showUrls(U);
    return 0;
}