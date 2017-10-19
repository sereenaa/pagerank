// urlType.h. Interface for linked lists of url data structure
// Jesse Colville

#ifndef URLTYPE_H
#define URLTYPE_H
#define BUFFSIZE 4096

typedef struct urlRep urlRep;
typedef struct url url;

// Helper functions
urlRep *urlRepCreate();
void insertURL(urlRep *, char*);
url *findLast(url *);
void showUrls(urlRep *);
int isMemberArg(char**, char*, int);
void countWord(urlRep *, char*);

#endif
