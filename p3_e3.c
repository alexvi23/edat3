#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include "list.h"

int main(int argc,char *argv[]){
    int i,num,j=1,tam;
    FILE *f;
    List *pl;
    List *pl2;
    void *aux,*aux2;

    if(argc<3){
        fprintf(stdout, "Error");
        return 0;
    }
    f=fopen(argv[2],"r");
    if(!f){
        return 0;
    }
    num=atoi(argv[3]);
    pl=list_new();
    if(!pl){
        fclose(f);
        return 0;
    }
    pl2=list_new();
    if(!pl){
        fclose(f);
        list_free(pl);
        return 0;
    }
    
    fscanf(f, "%d", &tam);
	while(fscanf(f, "%f", (float*)aux)==1){
		aux2=float_init(aux);
        if(j%2==0){
            list_pushFront(pl, (void*)aux2);
        }
        else{
            list_pushBack(pl,(void*)aux2);
        }
	}

    if(tam==(int)list_size(pl)){
        fprintf(stdout, "Error");
        return 0;
    }
    fprintf(stdout,"SIZE:%d",tam);
    list_print(stdout,pl,float_print);

    fprintf(stdout, "\nFinished inserting. Now we extract from the beginning and insert in order:\n");
    for(i=0;i<tam/2;i++){
        aux=list_popFront(pl);
        float_print(stdout, aux);
        list_pushInOrder(pl2,aux,float_cmp,num);
    }

    fprintf(stdout, "\nNow we extract from the end and insert in order:\n");
    while(list_isEmpty(pl)==FALSE){
        aux=list_popBack(pl);
        float_print(stdout, aux);
        list_pushInOrder(pl2,aux,float_cmp,num); 
    }

    fprintf(stdout,"SIZE:%d",tam);
    list_print(stdout,pl,float_print);

    float_free(aux2);

    return 0;
}