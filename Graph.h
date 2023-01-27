//*******************************************************************************
//
//Name : Paul Simbulan 
//CruzID : 1812663
//CSE102 Programming Assigment
//
//*******************************************************************************


#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NIL -1
#define UNDEF -2


typedef struct GraphObj* Graph; 


//
//creates and returns new Graph
//
Graph newGraph(int n);


//
//frees all memory allocated for Graph
//
void freeGraph(Graph *pG);

//
//returns number of vertices of Graph G
//
int getOrder(Graph G);


//
//returns number of edges in Graph G
//
int getSize(Graph G);




//
//adds edge on Graph G by joining u with v
//
void addEdge(Graph G, int u, int v);

//
//removes edge u,v
//
void removeEdge(Graph G, int u, int v);




//
//returns true if Graph G is acyclic.
//runs Depth first search alg. on G
//List s contains element of which DFS would run
//
bool isAcyclic(Graph G, List s);

//
//prints adjency list of Graph g on FILE out
//
void printGraph(FILE *out, Graph G);




#endif
