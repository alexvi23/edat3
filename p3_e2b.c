#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "vertex.h"
#include "file_utils.h"

int main(int argc, char **argv){
    FILE *f;
    Graph *g;
    int i;
    long from_id, to_id;

    f=fopen(argv[1], "r");
    if(f==NULL){
        return -1;
    }
    g=graph_init();
    if(g==NULL){
        fclose(f);
        return -1;
    }

    if(graph_readFromFile(f, g)==ERROR){
        fclose(f);
        graph_free(g);
        return -1;
    }
    from_id=atol(argv[2]);
    to_id=atol(argv[3]);

    fprintf(stdout, "Input graph:");
    graph_print(stdout, g);

    fprintf(stdout, "\n\n--------DFS------------");
    fprintf(stdout, "\nFrom vertex id: %ld\nTo vertex id: %ld\nOutput:\n", from_id, to_id);
    if(graph_depthSearch(g, from_id, to_id)==OK){
        for(i=0; i<g->num_vertices; i++){
            if(vertex_getState(g->vertices[i])==BLACK){
                vertex_print(stdout, g->vertices[i]);
                fprintf(stdout, "\n");
            }
        }
    }

    fprintf(stdout, "\n--------BFS------------");
    fprintf(stdout, "\nFrom vertex id: %ld\nTo vertex id: %ld\nOutput:\n", from_id, to_id);
    if(graph_breathSearch(g, from_id, to_id)==OK){
        for(i=0; i<g->num_vertices; i++){
            if(vertex_getState(g->vertices[i])==BLACK){
                vertex_print(stdout, g->vertices[i]);
                fprintf(stdout, "\n");
            }
        }
        graph_free(g);
        fclose(f);
        return 0;
    }

    return -1;
}
