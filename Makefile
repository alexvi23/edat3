########################################################
########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
EJS = p3_e1 p3_e2a
########################################################
OBJECTSP3E1 = p3_e1.o delivery.o file_utils.o libqueue.a vertex.o
OBJECTSP3E2A = p3_e2a.o delivery.o file_utils.o queue.o vertex.o
########################################################

all: $(EJS)

p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1)

p3_e2a:$(OBJECTSP3E2A)
	$(CC) $(CFLAGS) -o p3_e2a $(OBJECTSP3E2A)

p3_e1.o: p3_e1.c vertex.h delivery.h file_utils.h
	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2a.o: p3_e2a.c vertex.h delivery.h file_utils.h
	$(CC) $(CFLAGS) -c p3_e2a.c
	
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c
	
vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

graph.o: graph.c graph.h vertex.h stack.h
	$(CC) $(CFLAGS) -c graph.c
	
file_utils.o:file_utils.c file_utils.h
	$(CC) $(CFLAGS) -c file_utils.c

queue.o:queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)