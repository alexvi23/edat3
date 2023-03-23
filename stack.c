#include "stack.h"
#include "vertex.h"
#define INIT_CAPACITY 2 // init stack capacity
#define FCT_CAPACITY 2 // multiply the stack capacity

struct _Stack {
	void **item; /*!<Static array of elements*/
	int top; /*!<index of the top element in the stack*/
	int capacity; /*!<xcapacity of the stack*/
};

Status mergeStacks (Stack *s1, Stack *s2, Stack *sout, int (*func)()){
	Stack *saux;
	void *e;
	int aux;
	if(!s1||!s2||!sout){
		return ERROR;
	}
	while(stack_isEmpty(s1)==FALSE&&stack_isEmpty(s2)==FALSE){
		aux = func(stack_top(s1), stack_top(s2));
		if(aux==1){
			e=stack_pop(s1);
		}
		else{
			e=stack_pop(s2);
		}
		stack_push(sout,e);
	}
	if(stack_isEmpty(s1)==TRUE){
		saux=s2;
	}
	else{
		saux=s1;
	}
	while(stack_isEmpty(saux)==FALSE){
		e=stack_pop(saux);
		stack_push(sout,e);
	}
	return OK;
}

Stack *stack_init(){
	Stack *s;
	int i;
	s = (Stack *)malloc(sizeof(Stack));

	if (s == NULL) {
		return NULL;
	}

	s->item=(void**) malloc(INIT_CAPACITY*sizeof(void*));
	if(s->item==NULL){
		return NULL;
	}
	s->capacity=INIT_CAPACITY;
	for(i=0;i<s->capacity;i++){
		s->item[i]=NULL;
	}
	s->top = -1;
	return s;
}

void stack_free(Stack *s) {
	free(s->item);
	free(s);
}

Bool stack_isEmpty(const Stack *s) {
if (s == NULL) {
return TRUE;
}
if (s->top == -1) {
return TRUE;
}
return FALSE;
}

Bool _stack_isFull(const Stack *s) {
if (s == NULL) {
return TRUE;
}
if (s->top == s->capacity-1) {
return TRUE;
}
return FALSE;
}

Status stack_push(Stack *s, const void *e) {
	if (s == NULL || e == NULL) {
		return ERROR;
	}
	
	if(_stack_isFull(s)==TRUE){
		s->item=(void**) realloc(s->item, sizeof(Stack)*(s->capacity+FCT_CAPACITY));
		s->capacity=s->capacity+FCT_CAPACITY;
		if(s->item==NULL){
			return ERROR;
		}
	}
	s->top++;
	s->item[s->top] =(void *)e;
	return OK;
}

void *stack_pop(Stack *s) {
	void *e = NULL;
	if (s == NULL || stack_isEmpty(s) == TRUE) {
		return NULL;
	}
	e = s->item[s->top];
	s->item[s->top] = NULL;
	s->top --;
	return e;
}

void *stack_top(const Stack *s) {
	if (s == NULL || stack_isEmpty(s) == TRUE) {
		return NULL;
	}
		return s->item[s->top];
}

int stack_print(FILE* fp, const Stack *s,  P_stack_ele_print f){
	int i;
	if(!fp||!s){
		return -1;
	}
	fprintf(fp,"\nSIZE %d",s->top+1);
	for(i=s->top;i>=0;i--){
		fprintf(fp,"\n");
		f(fp,s->item[i]);
	}
	fprintf(fp,"\n");

	return i;
}

