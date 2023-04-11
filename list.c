
/**
 * @file list.c
 * @author ej76lo7
 * @date 6 April 2020
 * @brief Public interface for a Linked List implementation.
 */
#include "list.h"
typedef struct _NodeList{
  void* data;
  struct _NodeList *next;
}NodeList;
struct _List {
  NodeList *last;
};

int list_print(FILE *fp, const List *pl, P_ele_print f){
  NodeList *qn=NULL;
  int i,total,res;
  if(!pf||!pl||!f){
    return -1;
  }
  qn=pl->first;
  while(qn!=NULL){
    res=f(fp,qn->data);
    if(res<0){
      return res;
    }
    total+=f(fp,qn->data);
    qn = qn->next;
  }
  return total;
}


