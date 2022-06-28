#ifndef SESSION_H
    #define SESSION_H
#endif

#include "../buffer/recvbuffer.h"
#include "socketargs.h"
#include "../atomic_datastructure/atomic_queue.h"
#include "../log/log.h"
typedef struct SESSION
{
    RECVBUFFER* recvbuffer;
    atomic_QUEUE *sendqueue;
    SOCKETARGS* recv_args;
    SOCKETARGS* send_args;
    int session_socket;
    bool disconnected;
}SESSION;


void init_session(SESSION *session);
void clear(atomic_QUEUE *queue);
void start(int socket);
void disconnect(int socket);
void send_buff(BUFFER* buffer,SESSION *session);
void reg_send(SESSION *session);
void send_completed(void *sender,SESSION *session);
bool try_send(BUFFER *bufer,int socket,SESSION *session);
void reg_recv(SESSION *session);
bool try_recv(SESSION *session);
void recv_completed(void *sender,SESSION *session);

int on_recv(BUFFER* buffer);
void on_connect(int socket);
void on_send(int numofbytes);
void on_disconnect(struct sockaddr_in addr);
