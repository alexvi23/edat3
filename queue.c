#include "queue.h"

struct _Queue{
void *data[MAX_QUEUE];
void **front;
void **rear;
}

Queue * queue_new () {
    Queue *pq = NULL;
    int i;
    pq = ( Queue *) malloc ( sizeof ( Queue ));
    if (pq == NULL) {
        return NULL;
    }
    for (i = 0; i < MAX_QUEUE ; i++) {
        pq ->data[i] = NULL;
    }
    pq -> front = &pq->data[0];
    pq -> rear = &pq->data[0];
    return pq;
}

void queue_free (Queue *pq) {
free(pq);
}

Bool queue_isEmpty (const Queue *pq) {
if (pq == NULL) {
return TRUE;
}
if (pq -> front == pq ->rear) {
return TRUE;
}
return FALSE ;
}

Bool _queue_isFull (const Queue *pq) {
    if (pq == NULL) {
        return TRUE;
    }
    if ((pq ->rear + 1 - pq -> front ) % MAX_QUEUE == 0) {
        return TRUE;
    }
        return FALSE ;
}


Status queue_push (Queue *pq , const void *e) {
    if (pq == NULL || e == NULL || _queue_isFull (pq) == TRUE) {
        return ERROR ;
    }
    *(pq ->rear) = (void *)e;
    pq ->rear = pq ->data + (pq ->rear + 1 - pq ->data) % MAX_QUEUE ;
    return OK;
}

void * queue_pop (Queue *pq) {
    void *e = NULL;
    if (pq == NULL || queue_isEmpty (pq) == TRUE) {
        return NULL;
    }
    e = *(pq -> front );
    *(pq -> front ) = NULL;
    pq -> front = pq ->data + (pq -> front + 1 - pq ->data) % MAX_QUEUE ;
    return e;
}

void * queue_getFront (const Queue *pq) {
    if (pq == NULL || queue_isEmpty (pq) == TRUE) {
        return NULL;
    }
    return *(pq->front);
}

void * queue_getBack ( const Queue *pq) {
    void ** last_elem ;
    if (pq == NULL || queue_isEmpty (pq) == TRUE) {
        return NULL;
    }
    if (pq ->rear == pq ->data) {
        last_elem = (( Queue *) pq)->data + MAX_QUEUE - 1;
    } else {
        last_elem = pq ->rear - 1;
    }
    return * last_elem ;
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f){
    int i=0;
    Queue *aux
    void *e;
    char *pal;
    if(!fp||!q||!f){
        return 0;
    }
    aux=queue_new();
    if(!aux){
        return 0;
    }
    while(queue_isEmpty(pq)==FALSE){
        e=queue_pop(q);
        i+=f(fp,e);
        queue_push(aux,e);
    }
    while(queue_isEmpty(aux)==FALSE){
        e=queue_pop(aux);
        queue_push(q,e);
    }
    queue_free(aux);
    return i;
}