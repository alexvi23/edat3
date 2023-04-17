/**
 * @file  list.c
 * @author Carlos Viejo & Alejandro Vivas
 * @date 11 April 2023
 * @version 1.0
 * @brief Library to manage ADT List
 */

#include "list.h"
#include <math.h>

NodeList *node_new() {
  NodeList *pn = NULL;

  pn = malloc(sizeof(NodeList));
  if (!pn) {
    return NULL;
  }

  pn->data = NULL;
  pn->next = NULL;

  return pn;
}

/* Public function that creates a new List */
List *list_new () {
  List *pl = NULL;
  pl = (List *) malloc(sizeof(List));

  if (pl == NULL) {
    return NULL;
  }
  pl ->last = NULL;

  return pl;
}

/* Public function that checks if a List is empty */
Bool list_isEmpty (const List *pl) {
  if (pl == NULL) {
    return TRUE;
  }

  if (pl ->last == NULL) {
    return TRUE;
  }

  return FALSE;
}

/* Public function that pushes an element into the front position of a List */
// Delante de last
Status list_pushFront(List *pl, void *e){
  NodeList *pn;
  if (pl == NULL || e == NULL) {
    return ERROR;
  }

  pn = node_new ();
  if (pn == NULL) {
    return ERROR;
  }

  pn ->data = e;

  if (list_isEmpty(pl)) {
    pn ->next = pn;
    pl ->last = pn;
  } 
  else {
    pn ->next = pl ->last ->next;
    pl ->last ->next = pn;
  }

  return OK;
}

/* Public function that pushes an element into the back position of a List */
// Delante de last
Status list_pushBack(List *pl, void *e){
  NodeList *pn = NULL;
  if (pl == NULL || e == NULL) {
    return ERROR;
  }

  pn = node_new ();
  if (pn == NULL) {
    return ERROR;
  }

  pn ->data = e;

  if ( list_isEmpty (pl) == TRUE) {
    pn ->next = pn;
    pl ->last = pn;
  } 
  else {
    pn ->next = pl ->last ->next;
    pl ->last ->next = pn;
    pl ->last = pn;
  }

  return OK;
}

/* Public function that pushes an element into an ordered list */
Status list_pushInOrder (List *pl, void *e, P_ele_cmp f, int order){
  NodeList *pn = NULL , *qn = NULL, *rn = NULL;
  if (pl == NULL || e == NULL || order==0) {
    return ERROR;
  }

  pn = node_new();
  if(pn == NULL){
    return ERROR;
  }
  pn->data = e;

  if ( list_isEmpty (pl) == TRUE) {
    pn ->next = pn;
    pl ->last = pn;

    return OK;
  } 
  if(list_size(pl) == 1){
    if(order>0){
      list_pushBack(pl, e);
    } else {
      list_pushFront(pl, e);
    }
    free(pn);
    return OK;
  }

  if((f(pn->data, pl->last->data) >= 0 && order>0) || (f(pn->data, pl->last->data) <= 0 && order<0)){
    list_pushBack(pl, e);

    return OK;
  }
  if(order>0){
    qn=pl->last;
    do {
      rn=qn->next;
      if(f(pn->data, rn->data) <= 0){
        pn->next=rn;
        qn->next=pn;

        return OK;
      }
      qn = qn->next;
    } while(qn->data != pl->last->data);
  } else{
    qn=pl->last;
    do {
      rn=qn->next;
      if(f(pn->data, rn->data) >= 0){
        pn->next=rn;
        qn->next=pn;

        return OK;
      }
      qn = qn->next;
    } while(qn->data != pl->last->data);
  }

  return OK;
}

/* Public function that pops the front element from a List */
void * list_popFront (List *pl) {
  NodeList *pn = NULL;
  void *pe = NULL;
  if (pl == NULL || list_isEmpty(pl) == TRUE) {
    return NULL;
  }
  
  pn = pl ->last ->next;
  pe = pn ->data;
  
  if (pl ->last ->next == pl ->last) {
    pl ->last = NULL;
  } 
  else {
    pl ->last ->next = pn ->next;
  }
  free(pn);
  return pe;
}

/* Public function that pops the back element from a List */
void * list_popBack (List *pl) {
  NodeList *pn = NULL;
  void *pe = NULL;
  if (pl == NULL || list_isEmpty(pl) == TRUE) {
    return NULL;
  }

  if (pl ->last ->next == pl ->last) {
    pe = pl ->last ->data;
    free(pl ->last);
    pl ->last = NULL;
    return pe;
  }

  pn = pl ->last;
  while (pn ->next != pl ->last) {
    pn = pn ->next;
  }

  pe = pl ->last ->data;
  pn ->next = pl ->last ->next;

  free(pl ->last);
  pl ->last = pn;

  return pe;
}

/* Public function that frees a List */
void list_free (List *pl) {
  if (pl == NULL) {
    return;
  }

  while (list_isEmpty(pl) == FALSE) {
    free(list_popFront (pl));
  }

  free(pl);
}

size_t list_size(const List *pl){
  int i=0;
  NodeList  *node;
  if(!pl||list_isEmpty(pl)){
    return i;
  }
  node=pl->last;
  do{
    i++;
    node=node->next;
  } while(node!=pl->last);
  return i;
}

int list_print(FILE *fp, const List *pl, P_ele_print f){
  NodeList  *qn=NULL;
  int total=0,res;
  if(!fp||!pl||!f||list_isEmpty(pl)){
    return -1;
  }
  qn=pl->last;
  do {
    qn = qn->next;
    res=f(fp,qn->data);
    //printf("last [+%d] %f\n", total, *(float *)qn->data);
    if(res<0){
      return res;
    }
    total+=res;
    /*qn = qn->next;
    printf("next [+%d] %f\n", total, *(float *)qn->data);
    total++;
    printf("\n\n");*/
  } while(qn->data != pl->last->data);
  fprintf(fp, "\n");
  return total;
}
