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
int   isConnected(Graph, char *, char *);
void  showGraph(Graph,int);
// Jesse colville
// Number of edges for a vertex (degrees)
int nEdgesV(Graph, char *);

#endif
