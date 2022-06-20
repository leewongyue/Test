#include "listener.h"

void init_listener(SOCKADDR_IN addr,HANDLE comp_port,int backlog)
{
    if(WSAStartup(MAKEWORD(2,2),&wsaData))
    {
        LOG("WSAStartup failed");
        return ;
    }
    //완료 핸들러 초기화
    comp_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);

    listen_socket = WSASocket(AF_INET,SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
    if(listen_socket == SOCKET_ERROR)
    {
        LOG_ERRNO("Listen Socket Init failed",WSAGetLastError());
        return ;
    }
    if(bind(listen_socket,&addr,sizeof(addr)) == SOCKET_ERROR)
    {
        LOG("Socket Bind failed");
        return ;
    }
    listen(listen_socket,backlog);
    LOG("start listen");
    comp_port = CreateIoCompletionPort(listen_socket,comp_port,0,0);
    for(;;)
    {
        SOCK_ARGS *args;
        reg_accept(listen_socket,args);
    }
}
void reg_accept(SOCK_ARGS *args,HANDLE comp_port)
{
    BOOL pending;

    pending = accept_p(listen_socket,args);
    if(pending)
    {
        args->complete_port = CreateIoCompletionPort(args->accept_sock,comp_port,args->complete_key,0);
        accept_complete("",args);
    }
  
}

void accept_complete(void *sender,SOCK_ARGS *args)
{
    if(args->sock_state == S_ACCEPT)
    {
        args->sock_state = S_READ;
    }
}

BOOL accept_p(SOCKET listen_socket,SOCK_ARGS *args)
{
    init_sock_args(args);
    if(!AcceptEx(listen_socket,&args->accept_sock,&(args->buffer),0,sizeof(SOCKADDR_IN)+16,sizeof(SOCKADDR_IN) + 16, &args->transf_bytes,&(args->overlapped)))
    {
        if(WSAGetLastError != ERROR_IO_PENDING)
        {
            closesocket(args->accept_sock);
            LOG_ERRNO("Accept failed ",WSAGetLastError());
            free(args);
            return FALSE;
        }
    }
    return TRUE;
}

