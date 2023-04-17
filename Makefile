########################################################
########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
EJS = p3_e1 p3_e2a p3_e2b p3_e3
########################################################
OBJECTSP3E1 = p3_e1.o delivery.o file_utils.o libqueue.a vertex.o
OBJECTSP3E2A = p3_e2a.o delivery.o file_utils.o queue.o vertex.o
OBJECTSP3E2B = p3_e2b.o file_utils.o queue.o vertex.o graph.o stack.o
OBJECTSP3E3 = p3_e3.o file_utils.o list.o
########################################################

all: $(EJS)

p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1)

p3_e2a:$(OBJECTSP3E2A)
	$(CC) $(CFLAGS) -o p3_e2a $(OBJECTSP3E2A)

p3_e2b:$(OBJECTSP3E2B)
	$(CC) $(CFLAGS) -o p3_e2b $(OBJECTSP3E2B)

p3_e3:$(OBJECTSP3E3)
	$(CC) $(CFLAGS) -o p3_e3 $(OBJECTSP3E3)

p3_e1.o: p3_e1.c vertex.h delivery.h file_utils.h
	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2a.o: p3_e2a.c graph.h delivery.h file_utils.h
	$(CC) $(CFLAGS) -c p3_e2a.c

p3_e2b.o: p3_e2b.c graph.h vertex.h queue.h stack.h file_utils.h
	$(CC) $(CFLAGS) -c p3_e2b.c

p3_e3.o: p3_e3.c list.h file_utils.h
	$(CC) $(CFLAGS) -c p3_e3.c
	
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

list.o: list.c list.h file_utils.h
	$(CC) $(CFLAGS) -c list.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)
