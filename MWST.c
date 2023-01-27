//*******************************************************************************
//
//Name : Paul Simbulan 
//CruzID : 1812663
//CSE102 Programming Assigment
//
//*******************************************************************************


#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"



struct Edge
{
   int u;
   int v;
   int w;
};

int main(int argc, char* argv[]) 
{
  
FILE *inputFile;
FILE *outputFile;
  
   //following blocks are used for getting user input
   if(argc != 3)
   {
     fprintf(stderr, "incorrect number of arguments\n");
     exit(1);
   }
   inputFile = fopen(argv[1], "r");
   if( inputFile==NULL )
   {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
   }

   outputFile = fopen(argv[2], "w");
   if( outputFile==NULL )
   {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
   }
   
   //end of block user-input
   


  //u,v,w: variables used to store integers read from FILE input
  int u,v,w=0;
  //vertices_size: size of graph
  //edge_size: number of edges
  int vertices_size=0;
  int edge_size=0;
  
  fscanf(inputFile,"%d",&vertices_size);
  fscanf(inputFile,"%d",&edge_size);
  Graph G = newGraph(vertices_size);
  
  //S used DFS stack
  List S = newList();

  //stores value from 1 to size for DFS to run
  for(int i=1;i<=getOrder(G);i++)
  {
    append(S, i);
  }
  
  //Edge array containing edges;
  struct Edge edgeArray[edge_size];
  

  
  
  //reads user input edges and store in array edgeArray[]
  int i=0;
  while(    (fscanf(inputFile, "%d %d %d",&u,&v,&w) > 0) && (u != 0) && (v != 0) && (w != 0)  )
  {
    edgeArray[i].u = u;
    edgeArray[i].v = v;
    edgeArray[i].w = w;
    i++;
  }


  //
  //pq: priority queue for edges sorted min weight -> max weight
  List pq = newList();
  prepend(pq,0);
  for(int i=1; i<edge_size;i++)
  {
    moveBack(pq);
    while(index(pq) >= 0)
    {
      if(edgeArray[i].w >= edgeArray[get(pq)].w)
      {
        insertAfter(pq,i);
        break;
      }
      if(edgeArray[i].w < edgeArray[get(pq)].w)
      {
        movePrev(pq);
      }
    }
    if(index(pq) < 0)
    {
      prepend(pq,i);
    }
  }


  //edge_array2: sets to true if edge is used for min spanning tree
  //used to keep track of edges to print later

  bool edge_array2[edge_size];
  for(int i=0; i<edge_size; i++)
  {
    edge_array2[i] = false;
  }

  //edge_sum: sum of the edge weight used for min spanning tree
  int edge_sum = 0;
  
  //runs dfs algorithm to find if graph is acyclic
  //keeps adding edge to graph while graph G is not acyclic
  moveFront(pq);
  for(int i=0; i<edge_size; i++)
  {
    addEdge(G,edgeArray[get(pq)].u,edgeArray[get(pq)].v);
    edge_sum += edgeArray[get(pq)].w;
    edge_array2[get(pq)] = true;
    if(isAcyclic(G,S))
    {
      removeEdge(G,edgeArray[get(pq)].u,edgeArray[get(pq)].v);
      edge_sum -= edgeArray[get(pq)].w;
      edge_array2[get(pq)] = false;
    } 
    moveNext(pq);
  }

 

  
  //print output to outfile
  for(int i=0; i<edge_size; i++)
  {
    if(edge_array2[i])
    {
      fprintf(outputFile,"%d: (%d, %d) %.1f\n",(i+1),edgeArray[i].u,edgeArray[i].v,(edgeArray[i].w + 0.0));
    }
  }
  
  fprintf(outputFile,"Total Weight = %.2f\n",(edge_sum + 0.0));
  

  //frees memory allocated variables
  freeList(&S);
  freeList(&pq);
  freeGraph(&G);
  fclose(inputFile);
  fclose(outputFile);


  return 0;
}
  
