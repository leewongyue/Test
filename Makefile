CC = gcc
TARGET = main
CFLAGS = -Wall -Wextra -g -o $(TARGET)
OBJFLAG = -Wall -Wextra -c
OBJS = main.o queue.o buffer.o linkedlist.o


#HEADERS
HEADERS = datastructure/queue.h  datastructure/linkedlist.h
#BUFFER
BUFFER = buffer/buffer.h buffer/buffer.c
#DATASTRUCTURE
QUEUE = datastructure/queue.h datastructure/queue.c
LINKEDLIST = datastructure/linkedlist.h datastructure/linkedlist.c
#MAIN

buffer.o : $(BUFFER)
		$(CC) $(OBJFLAG) buffer/buffer.c
queue.o : $(QUEUE)
		$(CC) $(OBJFLAG) datastructure/queue.c
linkedlist.o : $(LINKEDLIST)
		$(CC) $(OBJFLAG) datastructure/linkedlist.c
main.o : $(HEADERS) main.c
		$(CC) $(OBJFLAG) main.c
main : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS)
