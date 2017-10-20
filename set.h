// set.h ... interface to simple Set of Strings
// Written by John Shepherd, September 2015
// Modified by Jesse Colville

#ifndef SET_H
#define SET_H

typedef struct SetRep *Set;

// Function signatures

Set newSet();
void disposeSet(Set);
void insertInto(Set,char *);
void dropFrom(Set,char *);
int  isElem(Set,char *);
int  nElems(Set);
void showSet(Set);
// Jesse Colville
char *getNth(Set, int);
int isEmpty(Set);

#endif
