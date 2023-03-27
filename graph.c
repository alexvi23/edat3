#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/*Private funcions*/

/*Consigue la posición en la que un vertex con cierto id o tag está en el array*/
int graph_getNumFromId(const Graph *g,long id);
int graph_getNumFromTag(const Graph *g,char *desc); /*Equivalente a int _graph_findVertexByTag*/

Status _graph_insertEdgeFromIndices(Graph *g, const long origIx, const long destIx);
int _graph_getNumConnections(const Graph *g, int ix);
long *_graph_getConnections(const Graph *g, int ix);
void _graph_setVertexState (Graph *g, Label l);

/*                  */


Graph * graph_init(){
    Graph *g;
    g=(Graph*) malloc(sizeof(Graph));
    if(!g){
        return NULL;
    }
    g->num_vertices=0;
    g->num_edges=0;

    return g;
}

void graph_free(Graph *g){
    int i;
    if(!g){
        return;
    }
    for(i=0;i<g->num_vertices;i++){
        vertex_free(g->vertices[i]);
    }
    free(g);
}

Status graph_newVertex(Graph *g, char *desc){
    int i;
    if(!g||!desc){
        return ERROR;
    }
    g->vertices[g->num_vertices]=vertex_initFromString(desc);
    for(i=0;i<g->num_vertices;i++){
        if(vertex_cmp(g->vertices[i],g->vertices[g->num_vertices])==0){
            vertex_free(g->vertices[g->num_vertices]);
            return OK;
        }
    }
	vertex_setIndex(g->vertices[g->num_vertices],g->num_vertices);
    (g->num_vertices)++;
    return OK;
}

Status graph_newEdge(Graph *g, long orig, long dest){
    int n1,n2;

    if(graph_contains(g,orig)==FALSE||graph_contains(g,dest)==FALSE){
        return ERROR;
    }

    n1=graph_getNumFromId(g,orig);
    n2=graph_getNumFromId(g,dest);

    g->connections[n1][n2]=TRUE;

    return OK;
}

Bool graph_contains(const Graph *g, long id){
    if(!g){
        return FALSE;
    }
    
    if(graph_getNumFromId(g,id)==-1){
        return FALSE;
    }
    return TRUE;
    
}

int graph_getNumberOfVertices(const Graph *g){
    if(!g){
        return -1;
    }
    return g->num_vertices;
}

int graph_getNumberOfEdges(const Graph *g){
    if(!g){
        return -1;
    }
    return g->num_edges;
}

Bool graph_connectionExists(const Graph *g, long orig, long dest){
    int n1,n2;
    if(!g||graph_contains(g,orig)==FALSE||graph_contains(g,orig)==FALSE){
        return FALSE;
    }
    n1=graph_getNumFromId(g,orig);
    n2=graph_getNumFromId(g,dest);

    if(g->connections[n1][n2]==TRUE){
        return TRUE;
    }
    return FALSE;
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id){
    int n1,n2,total;
    if(!g||graph_contains(g,id)==FALSE){
        return -1;
    }

    n1=graph_getNumFromId(g,id);

    for(n2=0,total=0;n2<g->num_vertices;n2++){
        if(g->connections[n1][n2]==TRUE){
            total++;
        }
    }
    return total;
}

long *graph_getConnectionsFromId(const Graph *g, long id){
    int i,j,k,total;
    long *ids;
    if(!g||graph_contains(g,id)==FALSE){
        return NULL;
    }
    total=graph_getNumberOfConnectionsFromId(g,id);
    if(total==0){
        return NULL;
    }
    ids=(long*) malloc(total*sizeof(long));

    if(!ids){
        return NULL;
    }

    i=graph_getNumFromId(g,id);

    for(j=0,k=0;j<g->num_vertices&&k<total;j++){
        if(g->connections[i][j]==TRUE){
            ids[k]=vertex_getId(g->vertices[j]);
            k++;
        }
    }
    return ids;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag){
    int i,j,total;
    if(!g||!tag){
        return -1;
    }
    for(i=0,j=0;i<g->num_vertices;i++){
        if(strcmp(vertex_getTag(g->vertices[i]),tag)==0){
            j=1;
            break;
        }
    }

    if(j==0){
        return -1;
    }

    total=graph_getNumberOfConnectionsFromId(g,vertex_getId(g->vertices[i]));
    return total;
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag){
    int i,j,total;
    long *ids;
    if(!g||!tag){
        return NULL;
    }
    total=graph_getNumberOfConnectionsFromTag(g,tag);
    if(total<=0){
        return NULL;
    }

    ids= (long*) malloc(total*sizeof(long*));

    if(!ids){
        return NULL;
    }

    for(i=0,j=0;i<g->num_vertices;i++){
        if(strcmp(vertex_getTag(g->vertices[i]),tag)==0){
            j=1;
            break;
        }
    }

    if(j==0){
        free(ids);
        return NULL;
    }

    ids=graph_getConnectionsFromId(g,vertex_getId(g->vertices[i]));

    return ids;
}

int graph_print (FILE *pf, const Graph *g){
    int i,j,printed;
    if(!pf||!g){
        return -1;
    }
    for(i=0,printed=0;i<g->num_vertices;i++){
        fprintf(pf,"\n");
        printed+=vertex_print(pf,g->vertices[i]);
        fprintf(pf,": ");
        for(j=0;j<g->num_vertices;j++){
            if(g->connections[i][j]==TRUE){
                printed+=vertex_print(pf,g->vertices[j]);
            }
        }
    }
    return printed;
}

int graph_getNumFromId(const Graph *g,long id){
    int i;
    for(i=0;i<g->num_vertices;i++){
        if(vertex_getId(g->vertices[i])==id){
            return i;
        }
    }
    return -1;
}

int graph_getNumFromTag(const Graph *g,char *desc){
    int i;
    for(i=0;i<g->num_vertices;i++){
        if(strcmp(vertex_getTag(g->vertices[i]),desc)==0){
            return i;
        }
    }
    return -1;
}

Status graph_readFromFile (FILE *fin, Graph *g){	
	int i, num_vert;
	long orig, dest;
	char descr[TAG_LENGHT];
	Label s=WHITE;
	
	if(!fin||!g){
		return ERROR;
  }
	
	fscanf(fin, "%d\n", &num_vert);
	
	for(i=0; i<num_vert; i++){
		fgets(descr, TAG_LENGHT, fin);
		if ((strlen(descr) > 0) && (descr[strlen(descr) - 1] == '\n')){
			descr[strlen(descr) - 1] = '\0';
		}
		graph_newVertex(g, descr);
		if(vertex_setState (g->vertices[i], s)==ERROR){
			return ERROR;
		}
	}
	
	while(fscanf(fin, "%ld %ld", &orig, &dest)==2){
		graph_newEdge(g, orig, dest);
		g->num_edges ++;
	}
	
	return OK;
}

Status _graph_insertEdgeFromIndices(Graph *g, const long origIx, const long destIx){
	long id1,id2;
	if(!g){
		return ERROR;
	}
	id1=vertex_getId(g->vertices[origIx]);
	id2=vertex_getId(g->vertices[destIx]);
	if(graph_newEdge(g,id1,id2)==ERROR){
		return ERROR;
	}
	return OK;				 
}
					 
int _graph_getNumConnections(const Graph *g, int ix){
	int id;
	if(!g){
		return -1;
	}
	id = vertex_getId(g->vertices[ix]);
	if(id == -1){
		return -1;
	}
	return graph_getNumberOfConnectionsFromId(g,id);
}					 
long *_graph_getConnections(const Graph *g, int ix){
	long id1;
	long *ids;
	if(!g){
		return NULL;
	}
	id1=vertex_getId(g->vertices[ix]);
	ids=graph_getConnectionsFromId(g,id1);				 
	if(ids==NULL){
		return NULL;
	}
	return ids;				 
}
					 
void _graph_setVertexState (Graph *g, Label l){
	int i, total;
	if(!g){
		return;
	}
	total=graph_getNumberOfVertices(g);
	if(total<1){
	return;
	}
	for(i=0;i<total;i++){
		vertex_setState(g->vertices[i],l);
	}
}

Status graph_depthSearch (Graph *g, long from_id, long to_id){
    Status st=OK;
    Stack *s;
    long *ids;
    void *aux_id;
    int i;
    
    if(!g){
        st=ERROR;
        return st;
    }
    _graph_setVertexState(g, WHITE);

    s=stack_init();
    stack_push(s, (long int*)from_id);

    while((stack_isEmpty(s)==FALSE) && st==OK){
        
        aux_id=stack_pop(s);
        if(vertex_getState(g->vertices[graph_getNumFromId(g, (long int)aux_id)])==WHITE){
            
            vertex_setState(g->vertices[graph_getNumFromId(g, (long int)aux_id)], BLACK);
            ids = graph_getConnectionsFromId(g, (long int)aux_id);
            
            for(i=0; i<graph_getNumberOfConnectionsFromId(g, (long int)aux_id); i++){
                if(vertex_getState(g->vertices[graph_getNumFromId(g, ids[i])])==WHITE){
                    
                    if(stack_push(s, (void*)ids[i])==ERROR){
                        st=ERROR;
                    }
                }
            }
        }
        
        if((long int)aux_id==to_id){
            break;
        }
        free(ids);
    }
    
    stack_free(s);
    return st;
}

Status graph_breathSearch (Graph *g, long from_id, long to_id){
    Status st=OK;
    Queue *q;
    long *ids;
    void *aux_id;
    int i;
    
    if(!g){
        st=ERROR;
        return st;
    }
    _graph_setVertexState(g, WHITE);

    q=queue_init();
    queue_push(s, (long int*)from_id);

    while((queue_isEmpty(s)==FALSE) && st==OK){
        
        aux_id=queue_pop(s);
        if(vertex_getState(g->vertices[graph_getNumFromId(g, (long int)aux_id)])==WHITE){
            
            vertex_setState(g->vertices[graph_getNumFromId(g, (long int)aux_id)], BLACK);
            ids = graph_getConnectionsFromId(g, (long int)aux_id);
            
            for(i=0; i<graph_getNumberOfConnectionsFromId(g, (long int)aux_id); i++){
                if(vertex_getState(g->vertices[graph_getNumFromId(g, ids[i])])==WHITE){
                    
                    if(queue_push(s, (void*)ids[i])==ERROR){
                        st=ERROR;
                    }
                }
            }
        }
        
        if((long int)aux_id==to_id){
            break;
        }
        free(ids);
    }
    
    queue_free(s);
    return st;
}
