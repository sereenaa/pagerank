// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015
// Modified by Jesse Colville

#ifndef GRAPH_H
#define GRAPH_H

typedef struct GraphRep *Graph;

// Function signatures

Graph newGraph(int);
void  disposeGraph(Graph);
int   addEdge(Graph,char *,char *); // args: Graph, source, destination
int   nVertices(Graph);
int   isConnectedOut(Graph, char *, char *);
void  showGraph(Graph,int);
// Jesse Colville
// Checks for inbound link
int   isConnectedIn(Graph, char *, char *);
// Jesse colville
int nEdgesInV(Graph, char *);
int nEdgesOutV(Graph, char*);
int outgoungFromOutgoing(Graph g, char *v);
int incomingFromOutgoing(Graph, char *);

#endif
