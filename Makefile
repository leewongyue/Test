CC = gcc
TARGET = main
CFLAGS = -Wall -Wextra -o $(TARGET)
OBJFLAG = -Wall -Wextra -c
OBJS = main.o queue.o buffer.o


#HEADERS
HEADERS = datastructure\queue.h buffer\buffer.h
#BUFFER 
BUFFER = buffer\buffer.h buffer\buffer.c
#DATASTRUCTURE
DATASTRUCTURE = datastructure\queue.h datastructure\queue.c
#MAIN

buffer.o : $(BUFFER)
		$(CC) $(OBJFLAG) buffer\buffer.c
queue.o : $(DATASTRUCTURE)
		$(CC) $(OBJFLAG) -c datastructure\queue.c
main.o : $(HEADERS) main.c
		$(CC) $(OBJFLAG) -c main.c
main : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS)
