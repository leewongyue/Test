#ifndef SESSION_H
    #define SESSION_H
#endif

#include "datastructure/queue.h"
#include "socketargs.h"

typedef struct SESSION
{
    SOCKET socket;
    int disconnected;

    
}SESSION;