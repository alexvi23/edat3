#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct _Queue{
void *data[MAX_QUEUE];
void **front;
void **rear;
};

Queue * queue_new () {
    Queue *q = NULL;
    int i;
    q = ( Queue *) malloc ( sizeof ( Queue ));
    if (q == NULL) {
        return NULL;
    }
    for (i = 0; i < MAX_QUEUE ; i++) {
        q ->data[i] = NULL;
    }
    q -> front = &q->data[0];
    q -> rear = &q->data[0];
    return q;
}

void queue_free (Queue *q) {
free(q);
}

Bool queue_isEmpty (const Queue *q) {
if (q == NULL) {
return TRUE;
}
if (q -> front == q ->rear) {
return TRUE;
}
return FALSE ;
}

Bool _queue_isFull (const Queue *q) {
    if (q == NULL) {
        return TRUE;
    }
    if ((q ->rear + 1 - q -> front ) % MAX_QUEUE == 0) {
        return TRUE;
    }
        return FALSE ;
}


Status queue_push (Queue *q , void *e) {
    if (q == NULL || e == NULL || _queue_isFull (q) == TRUE) {
        return ERROR ;
    }
    *(q ->rear) = (void *)e;
    q ->rear = q ->data + (q ->rear + 1 - q ->data) % MAX_QUEUE ;
    return OK;
}

void * queue_pop (Queue *q) {
    void *e = NULL;
    if (q == NULL || queue_isEmpty (q) == TRUE) {
        return NULL;
    }
    e = *(q -> front );
    *(q -> front ) = NULL;
    q -> front = q ->data + (q -> front + 1 - q ->data) % MAX_QUEUE ;
    return e;
}

void * queue_getFront (const Queue *q) {
    if (q == NULL || queue_isEmpty (q) == TRUE) {
        return NULL;
    }
    return *(q->front);
}

void * queue_getBack ( const Queue *q) {
    void ** last_elem ;
    if (q == NULL || queue_isEmpty (q) == TRUE) {
        return NULL;
    }
    if (q ->rear == q ->data) {
        last_elem = (( Queue *) q)->data + MAX_QUEUE - 1;
    } else {
        last_elem = q ->rear - 1;
    }
    return * last_elem ;
}

size_t queue_size(const Queue *q){
    if(!q){
        return 0;
    }
    return (q->rear-q->front+MAX_QUEUE)%MAX_QUEUE;
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f){
    int i=0;
    Queue *q2;
    Queue *aux;
    void *e;
    if(!fp||!q||!f){
        return 0;
    }
    q2=(Queue*)q;
    aux=queue_new();
    if(!aux){
        return 0;
    }
    while(queue_isEmpty(q2)==FALSE){
        e=queue_pop(q2);
        i+=f(fp,e);
        queue_push(aux,e);
    }
    while(queue_isEmpty(aux)==FALSE){
        e=queue_pop(aux);
        queue_push(q2,e);
    }
    fprintf(fp,"\n");
    queue_free(aux);
    return i;
}
