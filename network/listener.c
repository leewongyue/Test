

#include "listener.h"

void init_socket(struct sockaddr_in addr,SOCKETARGS *args,int port)
{
    int option = 1;
    memset(&listensocket,0,sizeof(listensocket));
    if((listensocket = socket(PF_INET,SOCK_STREAM,0)) == -1)
    {
        DEBUG_ERR("socket init failed",-1);
        return;
    }
    setsockopt(listensocket,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));

    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonll(INADDR_ANY);
    addr.sin_port = htons(port);
    option = bind(listensocket,(struct sockaddr*)&addr,sizeof(addr));
    if(option == -1)
    {
        DEBUG_ERR("socket bind failed",-1);
        return;
    }
}
bool accept_socket(int serversocket,SOCKETARGS *args)
{
    int addrsize = 0;
    if(serversocket == -1)
        return true;
    if((clientsocket = accept(listensocket,(struct sockaddr*)&args->client_addr,&addrsize)) == -1)
    {
        DEBUG_ERR("accept failed",-1);
        return true;
    }
    args->acceptsocket = clientsocket;
    return false;
}
void reg_accept(SOCKETARGS *args)
{
    args->acceptsocket = 0;

    if(accept_socket(listensocket,args))
    {
        return;
    }
    else
    {
        args->socketstate = STATE_ACCEPTED;
        accept_complete(args);
    }
}
void accept_complete(SOCKETARGS *args)
{
    if(args->socketstate == STATE_ACCEPTED)
    {

    }
    SOCKETARGS *args_ = malloc(sizeof (SOCKETARGS));
    reg_accept(args_);
}
