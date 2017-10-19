// keyType.h used primarily ion inverted index
#ifndef KEYTYPE_H
#define KEYTYPE_H

typedef struct lListRep lListRep;

typedef struct key key;

typedef struct urlNode urlNode;

// Function signatures
lListRep *createLList();
void addWord(lListRep *, char *);
int findWord(lListRep *, char *);
void addURL(lListRep *, char *, char *);
int findURL(key *, char *);
void showlListRep(lListRep *);
void printInverted(lListRep *);

#endif