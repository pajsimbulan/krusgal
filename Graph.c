//*******************************************************************************
//
//Name : Paul Simbulan 
//CruzID : 1812663
//CSE102 Programming Assigment
//
//*******************************************************************************



#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>


//struct Graph
//adj- an array of list whose 'i'th element is a List composed of all its adjacent vertices
//parents- int array whose 'i'th element is a parent of index i;
//distance- int array whose 'i'th element is the shortest distance between source and vertex u.  u is index of array
//color- char array whose 'i'th element is the color of u.  u is index of array.
//order- number of vertices in Graph
//edge- number of edges
//recent- recent source data used.
typedef struct GraphObj{
   List *adj;
   int *disc_time;
   int *fin_time;
   int *parents;
   char *color;
   int order;
   int edge;
} GraphObj;

//
//allocates memory for a graph and returns it
//n is number of vertices in Graph
//
Graph newGraph(int n)
{
  Graph G = (GraphObj *)malloc(sizeof(GraphObj));
  //if mem alloc fails, return NULL
  if(!G)
  {
    return NULL;
  }
  //arraySize n+2 so index corresponds to data.
  int arraySize = n+1;
  G->adj = (List *)malloc(sizeof(List)*arraySize);
  G->parents =  (int *)malloc(sizeof(int)*arraySize);
  G->disc_time = (int *)malloc(sizeof(int)*arraySize);
  G->fin_time = (int *)malloc(sizeof(int)*arraySize);
  G->color = (char *)malloc(sizeof(char)*arraySize);
  G->order = n;
  G->edge = 0;
 
  if( (!G->adj) || (!G->color) || (!G->parents) || (!G->disc_time)  ||  (!G->fin_time) )
  {
    return NULL;
  }

  for(int i =0;i<=G->order;i++)
  {
    G->adj[i] = newList();
    G->parents[i] =  NIL;
    G->disc_time[i] = UNDEF;
    G->fin_time[i] = UNDEF;
  }
  return G;

}


//
//frees graph *pG
//
void freeGraph(Graph *pG)
{
  if( ((*pG) != NULL))
  {
    //frees every List first in array of List adj[i]
    for(int i=0; i<=  ( (*pG)->order);i++)
    {
      free((*pG)->adj[i]);
    }
    free((*pG)->adj);
    free((*pG)->color);
    free((*pG)->parents);
    free((*pG)->disc_time);
    free((*pG)->fin_time);
    free((*pG));
    *pG = NULL;
  }
}


//
//returns number of vertices
//
int getOrder(Graph G)
{   
  return (G->order);
}


//
//returns number of vertices
//
int getSize(Graph G)
{
  return (G->edge);
}


//
//removes edge u,v
//
void removeEdge(Graph G, int u, int v)
{

  if(!G)
  {
    return false;
  }

  if(u == v)
  {
    return false;
  }

  if( (u<=G->order) && (v<=G->order) && (u>=1)  && (v>=1) )
  {
    
    //removing v to adj list of u
    moveFront(G->adj[u]);
    while(index(G->adj[u]) >= 0)
    {
      if(get(G->adj[u]) == v)
      {
        delete(G->adj[u]);
        break;
      }
      moveNext(G->adj[u]);
    }

    moveFront(G->adj[v]);
    while(index(G->adj[v]) >= 0)
    {
      if(get(G->adj[v]) == u)
      {
        delete(G->adj[v]);
        break;
      }
      moveNext(G->adj[v]);
    }
  }

}




//
//adds edge by joining u and v
//
void addEdge(Graph G, int u, int v)
{
  //if joining by itself, then return and do nothing
  if(u==v)
  {
    return;
  }


  //if value of u and v within Graph size
  if( (u<=G->order) && (u>=1)  && (v>=1)  &&  (v<=G->order)  )
  {
    G->edge +=1;
  
  //following if block appends v to adj list of u
  //uses insertion sort
  if(length(G->adj[u]) <=0)
  {
    append(G->adj[u], v);
  }
  else
  {
    moveFront(G->adj[u]);
    while(index(G->adj[u])>=0)
    {
      if(v>=get(G->adj[u]))
      {
        moveNext(G->adj[u]);
        if(index(G->adj[u])<0)
        {
          append(G->adj[u],v);
        }
      }
      else
      {
        insertBefore(G->adj[u],v);
        break;
      }
    }//end of while
  }//end of else
  //end of insertion of v to adj list of u


//following if block appends u to adj list of v
//uses insertion sort
  if(length(G->adj[v]) <=0)
    {
    append(G->adj[v], u);
    }
    else
    {
      moveFront(G->adj[v]);
      while(index(G->adj[v])>=0)
      {
        if(u>=get(G->adj[v]))
        {
          moveNext(G->adj[v]);
          if(index(G->adj[v])<0)
          {
            append(G->adj[v],u);
          }
        }
        else
        {
          insertBefore(G->adj[v],u);
          break;
        }
      }//end of while
    }//end of else
    //end of insertion of u to adj list of v
  }//end of most outest if block 

}//end of function addEdge


//
//List 's'contains elements ofwhich DFS would try to run in order
//List 'temp' is a stack that pushes element of Graph G that were already finished
//sets List s to temp.
//
bool isAcyclic(Graph G, List S)
{
  List temp =newList();
  bool isacyclic = false;
  for(int i=1;i<=G->order;i++)
  {
    G->color[i] = 'W';
    G->parents[i] = NIL;
  }
  moveFront(S);
  while(index(S)>=0)
  {
    if(G->color[get(S)] == 'W')
    {
      visit(G,get(S),temp,&isacyclic);
    }
    moveNext(S);  
  }

  clear(S);
  moveFront(temp);
  
  while(index(temp)>=0)
  {
    append(S, get(temp));
    moveNext(temp);
  }

  free(temp);
  return isacyclic;
}

//
//helper function for DFS
//sets 'u' to'G'if its been discovered.  sets to U when it is finished
//
void visit(Graph G,int u,List S, bool *isacyclic)
{
  G->color[u] = 'G';
  moveFront(G->adj[u]);
  while(index(G->adj[u]) >=0)
  {
    int v = get(G->adj[u]);
    if( (G->color[v] == 'G') && ( !(G->parents[v] == u) || (G->parents[u] == v) ) )
    {
      if(G->parents[u] == v){}
      else if(G->parents[v] == u ){}
      else
      {
        *isacyclic = true;
      }
    
      
    }
    if(G->color[v] == 'W')
    {
      G->parents[v] = u;
      visit(G,v,S,isacyclic);
    }
    moveNext(G->adj[u]);
  }
  G->color[u] = 'B';
  prepend(S,u);
}


//
//prints adjency list of Graph G
//on FILE out
//
void printGraph(FILE *out, Graph G)
{
  for(int i=1; i<=G->order;i++)
  {
    moveFront(G->adj[i]);
    fprintf(out,"%d: ",i);
    while( index(G->adj[i])>=0  )
    {
      fprintf(out,"%d ",get(G->adj[i]));
      moveNext(G->adj[i]);
    }
    fprintf(out,"\n");
  }
}

