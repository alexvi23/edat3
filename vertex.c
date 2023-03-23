#include "vertex.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/


Status vertex_setField (Vertex *v, char *key, char *value);

Status vertex_setField (Vertex *v, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/

struct _Vertex {
  long id;
  char tag[TAG_LENGHT];
  Label state;
  int index;
};

Vertex *vertex_initFromString(char *descr){
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr) return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v) return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token) {
    p = strchr(token, ':');
    if (!p) continue;

    *p = '\0';
    key = token;
    value = p+1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

/**  rest of the functions in vertex.h **/

Vertex * vertex_init (){
  Vertex * v;
  v =(Vertex*) malloc(sizeof(Vertex));
  if(!v){
    return NULL;
  }
  v->id=0;
  strcpy(v->tag,"");
  v->state=WHITE;

  return v;
}

void vertex_free (void * v){
	free(v);
}

long vertex_getId (const Vertex * v){
	if(!v){
		return -1;
	}
	return v->id;
}

const char* vertex_getTag (const Vertex * v){
	if(!v){
		return NULL;
	}

	return v->tag;
}

Label vertex_getState (const Vertex * v){
	if(!v){
		return ERROR_VERTEX;
	}
	return v->state;
}

int vertex_getIndex(const Vertex *v){
  if(!v){
    return -1;
  }
  return v->index;
}

Status vertex_setId (Vertex * v, const long id){
	if(id<0||!v){
		return ERROR;
	}
	v->id=id;
	return OK;
}

Status vertex_setTag (Vertex * v, const char * tag){
  if(strlen(tag)>=64||!v||!tag){
    return ERROR;
  }
  strcpy(v->tag,tag);
  return OK;
}

Status vertex_setState (Vertex * v, const Label state){
  if(!v||state<0){  
    return ERROR;
  }
  v->state=state;
  return OK;
}

Status vertex_setIndex(Vertex *v, int Index){
  if(!v){
    return ERROR;
  }
  v->index = Index;
  return OK;
}

int vertex_cmp (const void * v1, const void * v2){
  const Vertex *v_1,*v_2;
  v_1=v1;
  v_2=v2;

  if(!v1||!v2){
    return 0;
  }
  if(v_1->id<v_2->id){
    return -1;
  }
  else if(v_1->id>v_2->id){
    return 1;
  }
  else{
    return strcmp(v_1->tag,v_2->tag);
  }
}

void * vertex_copy (const void * src){
  Vertex *v;
  const Vertex *src1;
  src1=src;
  if(!src){
    return NULL;
  }
  v=vertex_init();
  if(!v){
    return NULL;
  }
  v->id=src1->id;
  strcpy(v->tag,src1->tag);
  v->state=src1->state;
  return v;
}

int vertex_print (FILE * pf, const void * v){
  const Vertex *v1;
  int i;
  char pal[TAG_LENGHT];
  if(!pf||!v){
    return -1;
  }
  v1=v;

  fprintf(pf,"[");
  fprintf(pf,"%ld,",v1->id);
  fprintf(pf," %s,",v1->tag);
  fprintf(pf," %d,",v1->state);
  fprintf(pf," %d", v1->index);
  fprintf(pf,"]");
  
  for(i=0;fscanf(pf,"%s",pal)==1;i++);

  return i;
}

