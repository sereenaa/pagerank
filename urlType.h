// urlType.h. Interface for linked lists of url data structure
// Jesse Colville and Serena Xu

#ifndef URLTYPE_H
#define URLTYPE_H
#define BUFFSIZE 4096

typedef struct urlRep urlRep;
typedef struct url url;

// Function signatures
urlRep *urlRepCreate();
int insertURL(urlRep *, char*);
url *findLast(url *);
void showUrls(urlRep *);
int isMemberArg(char**, char*, int);
void countWord(urlRep *, char*);
void lowerArgs(int, char **);
void modTf(urlRep *, char*, char*);
void calcTfIdf(urlRep *, int, int);
void printUrlsC(urlRep *);
void printPart2(urlRep *);

#endif
