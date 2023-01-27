//*******************************************************************************
//
//Name : Paul Simbulan 
//CruzID : 1812663
//CSE102 Programming Assigment
//
//*******************************************************************************


#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;


// private Node type
typedef struct NodeObj* Node;


// private ListObj type
typedef struct ListObj{
   Node front;
   Node cursor;
   Node back;
   int length;
   int index;
} ListObj;


// private
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data)
{
   Node N = (Node)malloc(sizeof(NodeObj));
   if(!N)
   {
     exit(1);
   }
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}


// private
// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN)
{
   if( pN!=NULL && *pN!=NULL )
   {
      free(*pN);
      *pN = NULL;
   }
   return;
}



List newList(void)
{
  List l = (List) malloc(sizeof(ListObj));
  if(!l)
  {
    exit(EXIT_FAILURE);
  }
  l->front = NULL;
  l->back = NULL;
  l->cursor = NULL;
  l->length = 0;
  l->index = -1;
  return(l);
}


//frees variable of list first 
//then frees list
void freeList(List* pL)
{
  if(pL!=NULL && *pL!=NULL) { 
      clear(*pL);

      free(*pL);
      *pL = NULL;
   }
}


//returns list length
int length(List L)
{
  return(L->length);
}


//returns index of cursor
int index(List L)
{
  return(L->index);
}


//sets cursor to front(index 0) of the list
//and returns data
int front(List L)
{
  if( L==NULL)
  {
    exit(EXIT_FAILURE);
  }
  else if(L->length <=0)
  {
    exit(EXIT_FAILURE);
  }
  else
  {
    return L->front->data;
  } 
}


//sets cursor to back of list(length-1) of the list
//and returns data
int back(List L)
{
  if( L==NULL)
  {
    exit(EXIT_FAILURE);
  }
  else if(L->length <=0)
  {
    exit(EXIT_FAILURE);
  }
  else 
  {
    return L->back->data;
  } 
}


//gets data that the cursor points to
//if length >0 and index is not out of bounds (index = -1)
int get(List L)
{
  if(L == NULL)
  {
    exit(EXIT_FAILURE);
  }
  else if(   (L->length<=0) || (L->index < 0))
  {
    exit(EXIT_FAILURE);
  }
  
    return (L->cursor->data);
  
}


//compares list
//returns 1 if both list are equals
//returns 0 otherwise
int equals(List A, List B)
{
  int isEqual=1;
  
  if((A==NULL) || (B==NULL))
  {
    exit(EXIT_FAILURE);
  }
  if(length(A) != length(B))
  {
    return 0;
  }

  moveFront(A);
  moveFront(B);
  
  while( (index(A)>= 0) && (index(B) >= 0) )
  {
    if(get(A) != get(B))
    {
      isEqual =0;
      break;
    }
    moveNext(A);
    moveNext(B);
  } 
    return isEqual;
}

//clears elements of the list by iterating and freeing 
//each element
void clear(List L)
{
  if(L == NULL)
  {
    return;
  }
  if(length(L) == 0)
  {
    return;
  }

  moveFront(L);

  while(index(L)>=0)
  {
    delete(L);
    moveFront(L);
  }

  L->length =0; 
  return;
}


//sets data that the cursor points to
//with integer 'x' 
void set(List L, int x)
{
  if(L==NULL)
  {
    exit(EXIT_FAILURE);
  }
  if( L->length <= 0)
  {
    exit(EXIT_FAILURE);
  }
  if(L->index <0)
  {
    exit(EXIT_FAILURE);
  }

    L->cursor->data = x;

  return;

}


//moves cursor to the front of the list (index = 0)
void moveFront(List L)
{
  if(L==NULL)
  {
    exit(EXIT_FAILURE);
  }
  if(L->length <= 0)
  {
    return;
  }

  
  L->cursor = L->front;
  L->cursor->next = L->front->next;
  L->cursor->prev = NULL;
  L->index = 0;
  return;
}


//moves cursor to the back of the list (index = length-1)
void moveBack(List L)
{
 if(L==NULL)
  {
    exit(EXIT_FAILURE);
  }
  if(L->length <= 0)
  {
    return;
  }

  
  L->cursor = L->back;
  L->cursor->prev = L->back->prev;
  L->cursor->next = NULL;
  L->index = (length(L)-1);
  return;
}

//moves cursor a step towards the front( index = index-1)
//if index is already at the front, cursor goes out of bounds
//index = -1;
void movePrev(List L)
{
  if(L == NULL)
  {
    exit(EXIT_FAILURE);
  }
  if(L->length <= 0)
  {
    return;
  }
  else if(L->index < 0)
  {
    return;
  }
  else if(L->index == 0)
  {
    L->cursor = NULL;
    L->index = -1;
  }
  else
  {
    L->cursor = L->cursor->prev;
    L->index -= 1;
  }
}

//moves cursor a step towards the back( index = index+1)
//if index is already at the back, cursor goes out of bounds
//index = -1;
void moveNext(List L)
{
  if(L == NULL)
  {
   exit(EXIT_FAILURE);
  }
  if(L->length <= 0)
  {
    return;
  }
  else if(L->index < 0)
  {
    return;
  }
  else if(L->cursor == L->back)
  {
    L->cursor = NULL;
    L->index = -1;
  }
  else
  {
    L->cursor = L->cursor->next;
    L->index += 1;
  }

}


//adds an element to front of the list
void prepend(List L, int x)
{
  Node temp = newNode(x);
  if(L == NULL)
  {
    exit(EXIT_FAILURE);
  }

  if(L->length <= 0)
  {
    L->front = temp;
    L->back = L->front;
  }
  else
  {   
    L->front->prev = temp;
    temp->next = L->front;
    L->front = temp;  
  }
   L->length += 1;
   if(index(L) >=0)
   {
     L->index +=1;
   }
  return;
} 


//adds an element to the back of the list
void append(List L, int x)
{
  Node temp = newNode(x);

  if(L == NULL)
  {
    exit(EXIT_FAILURE);
  }
  if(L->length <= 0)
  {
    L->front = temp;
    L->back = L->front;
  }
  else
  {   
    L->back->next = temp;
    temp->prev = L->back;
    L->back = temp; 
  }
   L->length += 1;
} 


//insert an element at the index before the cursor index
void insertBefore(List L, int x)
{
  if(L == NULL)
  {
     exit(EXIT_FAILURE);
  }
  if(  (L->length <= 0)  ||  (L->index<0)  )
  {
     exit(EXIT_FAILURE);
  }



  if(L->index > 0)
  {
    Node temp = newNode(x);
    temp->next = L->cursor;
    temp->prev = L->cursor->prev;
    (L->cursor->prev)->next = temp;
    L->cursor->prev = temp;
    L->length += 1;
    L->index +=1;
  }
  else
  {
    prepend(L,x);
  }

}


//insert an element at the index after the cursor index
void insertAfter(List L, int x)
{
  if(L==NULL)
  {
     exit(EXIT_FAILURE);
  }

  if(  (L->length <= 0)  ||  (L->index<0)  )
  {
     exit(EXIT_FAILURE);
  }
  
  if(index(L) == (length(L)-1) )
  {
    append(L,x);
  }
  else
  {
    Node temp = newNode(x);
    temp->prev = L->cursor;
    temp->next = L->cursor->next;
    (L->cursor->next)->prev = temp;
    L->cursor->next= temp;
    L->length += 1;
  }
    
  return;
}


//deletes front element of the list
void deleteFront(List L)
{
  if(L==NULL)
  {
     exit(EXIT_FAILURE);
  }
  if(L->length <=0)
  {
     exit(EXIT_FAILURE);
  }
  if(L->length == 1)
  {
    freeNode(&L->front);
    L->cursor = NULL;
    L->index = -1;
  }
  else
  {
    
    L->front = L->front->next;
    freeNode(&L->front->prev);
    L->front->prev = NULL;
    L->index -= 1;
  }
  L->length -= 1;
  return;
}


//deletes the back element of the list
void deleteBack(List L)
{
  if(L == NULL)
  {
    exit(EXIT_FAILURE);
  }
  if(L->length <= 0)
  {
    exit(EXIT_FAILURE);
  }
  if(L->cursor == L->back)
  {
    L->cursor = NULL;
    L->index = -1;
  }

  if(L->back->prev != NULL)
  {
    L->back = L->back->prev;
    freeNode(&L->back->next);
    L->back->next = NULL;
  }
  else
  {
    freeNode(&L->back);
  }
  
    
  L->length -= 1;
  
}


//deletes the element the cursor points to
//sets cursor out of bounds (index = -1)
//after deleting element
void delete(List L)
{
  if(L== NULL)
  {
    exit(EXIT_FAILURE);
  }
  if( (L->length <= 0) || (L->index <0))
  {
    exit(EXIT_FAILURE);
  }
  if(L->index==0)
  {
    deleteFront(L);
    L->cursor = NULL;
    L->index = -1;
  }
  else if(L->index == (L->length-1))
  {
    deleteBack(L);
    L->cursor = NULL;
    L->index = -1;
    
  }
  else
  {
  (L->cursor->prev)->next = L->cursor->next;
  (L->cursor->next)->prev = L->cursor->prev;
  freeNode(&L->cursor);
  L->length -= 1;
  L->index = -1;
  L->cursor = NULL;
  }
  return;
}


//prints contents of the list
void printList(FILE* out, List L)
{
  moveFront(L);
  while(index(L) >=0)
  {
    fprintf(out,"%d ",get(L));
    moveNext(L);
  }
  printf("\n");
}


//returns a List identical to the parameter
List copyList(List L)
{
  List list = newList();
  if(L == NULL)
  {
    return list;
  }
  if(L->length <= 0)
  {
    
    return list;
  }

  moveFront(L);
  while(L->index >=0)
  {
    append(list, get(L));
    moveNext(L);
  }
  moveFront(list);
  moveFront(L);

  return list;
}
 

//returns a new list that is the combination of List A and List B
List concatList(List A, List B)
{
  List list = copyList(A);
  moveFront(B);
  while(index(B)>=0)
  {
    append(list, get(B));
    moveNext(B);
  }
  return list;
}
