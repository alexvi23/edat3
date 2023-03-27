#include <stdio.h>
#include <stdlib.h>
#include "delivery.h"
#include "vertex.h"

#define MAX_PAL 128

Delivery* build_delivery(FILE *pf){
    Delivery* d;
    char aux_name[MAX_PAL], aux_productName[MAX_PAL], str[MAX_PAL];
    int num, i;
    Vertex *v;
    
    if(!pf){
        return NULL;
    }
    
    fscanf(pf, "%s %s", aux_name, aux_productName);
    d=delivery_init(aux_name, aux_productName);
    if(!d){
        fclose(pf);
        return NULL;
    }
    num=fscanf(pf, "%d\n", &num);

    for(i=0; fgets(str, TAG_LENGHT, pf)!=NULL; i++){
        v=vertex_initFromString(str);
        delivery_add(stdout, d, (void*)v, vertex_print);
    }

    fclose(pf);

    return d;
}

int main(int argc, char **argv){
    FILE *f;
    Delivery *d;
    f=fopen(argv[1], "r");
    if(!f){
        return -1;
    }
    d=build_delivery(f);
    if(!d){
        return -1;
    }

    if(delivery_run_plan(stdout, d, vertex_print, vertex_free)==ERROR){
        return -1;
    }
    fprintf(stdout, "\n");


    delivery_free((void*)d);

    return 0;
}