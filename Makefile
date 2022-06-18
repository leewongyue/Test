CC = gcc
TARGET = main
CFLAGS = -Wall -Wextra -o $(TARGET)
OBJFLAG = -Wall -Wextra -c
OBJS = main.o queue.o buffer.o linkedlist.o KISA_SHA256.o hashtable.o jsonparser.o
#HEADERS
HEADERS = datastructure/queue.h datastructure/linkedlist.h buffer/buffer.h datastructure/hashtable.h packetgenerator/jsonparser.h

#NETWORK
###BUFFER
BUFFER = buffer/buffer.h buffer/buffer.c

#DATASTRUCTURE
QUEUE = datastructure/queue.h datastructure/queue.c
LINKEDLIST = datastructure/linkedlist.h datastructure/linkedlist.c
HASHMAP = datastructure/hashtable.h datastructure/hashtable.c

#SHA256
SHA256 = SHA256/KISA_SHA256.h SHA256/KISA_SHA256.c

#PACKETGENERATOR
PACKETGENERATOR = $(JSONPARSER) packetgenerator/packetformat.h
#####JSONPARSER
JSONPARSER = packetgenerator/jsonparser.h packetgenerator/jsonparser.c

jsonparser.o: $(JSONPARSER)
		#(CC) $(OBJFLAG) packetgenerator/jsonparser.c
hashtable.o: $(HASHMAP)
		$(CC) $(OBJFLAG) datastructure/hashtable.c
KISA_SHA256.o: $(SHA256)
		$(CC) $(OBJFLAG) SHA256/KISA_SHA256.c
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
clean:
	rm -rf $(OBJS) main a.out
