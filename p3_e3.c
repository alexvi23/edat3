#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include "list.h"

int main(int argc,char *argv[]){
    int i,num,j=1,tam, k=0;
    FILE *f;
    List *pl;
    List *pl2;
    float *elements[MAX_ELEM], scan;

    if(argc<2){
        fprintf(stdout, "Error");
        return 0;
    }
    f=fopen(argv[1],"r");
    if(!f){
        return 0;
    }
    num=atoi(argv[2]);
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
    
    fscanf(f, "%d", &tam); // Número de elementos
	while(fscanf(f, "%f", &scan)==1){
		elements[k]=float_init(scan);
        if(j%2==0){
            list_pushFront(pl, (void*)elements[k]);
        }
        else{
            list_pushBack(pl,(void*)elements[k]);
        }
        j++;
        k++;
	}

    fprintf(stdout,"SIZE:%d\n",tam);
    list_print(stdout,pl,float_print);

    fprintf(stdout, "\nFinished inserting. Now we extract from the beginning and insert in order:\n");
    for(i=0;i<tam/2;i++,k++){
        elements[k]=(float*)list_popFront(pl);
        float_print(stdout, (void*)elements[k]);
        //printf("\n");
        list_pushInOrder(pl2,(void*)elements[k],float_cmp,num);
        //list_print(stdout,pl2,float_print);
    }

    fprintf(stdout, "\nNow we extract from the end and insert in order:\n");
    while(list_isEmpty(pl)==FALSE){
        elements[k]=list_popBack(pl);
        float_print(stdout, elements[k]);
        //printf("\n");
        list_pushInOrder(pl2,elements[k],float_cmp,num);
        //list_print(stdout,pl2,float_print);
        k++;
    }

    fprintf(stdout,"\n\nSIZE:%d\n",tam);
    list_print(stdout,pl2,float_print);

    list_free(pl);
    list_free(pl2);

    fclose(f);

    return 0;
}