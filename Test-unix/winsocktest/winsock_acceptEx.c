#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <mswsock.h>

#pragma comment(lib,"mswsock.lib")
#pragma comment(lib, "ws2_32.lib")

#define ACCEPT_BUFF_SIZE 1024
#define MAX_BUFFSIZE  2048
int main()
{

    printf("==================================================================\n");
    WSADATA wsadata;
    SOCKET listen_sock, recv_sock;
    SOCKADDR_IN listen_addr, recv_addr;
    //함수포인터
    LPFN_ACCEPTEX lpfnAcceptEx = NULL;
    //함수포인터 
    LPFN_GETACCEPTEXSOCKADDRS lpfnGetAcceptExSockaddrs = NULL;
    //acceptex 가이드 
    GUID GuidAcceptEx = WSAID_ACCEPTEX;
    
    WSAOVERLAPPED Overapped;
    DWORD recvBytes,dwbytes;

    HANDLE hcompPort;
    HANDLE hcompPort1;

    char acceptbuff[ACCEPT_BUFF_SIZE];
    char buffer[MAX_BUFFSIZE];
    int mode = 1;

    //WSinit
    if(WSAStartup(MAKEWORD(2,2),&wsadata) !=0)
        printf("ERR LOG : WS INIT FAILED \n");

    //완료처리할 handle 초기화
    hcompPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,(u_long)0,0);
    if(hcompPort == NULL)
        printf("ERR LOG : CreateIOcompletionPort failed \n");
    //listensocket init
    listen_sock = WSASocket(PF_INET,SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
    //accept 등 작업들 대기하지 않도록 논블로킹 설정
    // ioctlsocket(listen_sock,FIONBIO,&mode);

    // listensocket에 대한 완료 포트 생성
    CreateIoCompletionPort((HANDLE) listen_sock, hcompPort, (u_long) 0, 0);

    listen_addr.sin_family=AF_INET;
    listen_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    listen_addr.sin_port = htons(6000);

    if(bind(listen_sock,(SOCKADDR*)&listen_addr,sizeof(listen_addr))==SOCKET_ERROR)
        printf("ERR LOG : BIND FAILED \n");
    // return 1;

    if(listen(listen_sock,2)==SOCKET_ERROR)
        printf("ERR LOG : LISTEN ERROR \n");
    // // return 1;

    // WSAIoctl(listen_sock,SIO_GET_EXTENSION_FUNCTION_POINTER,&GuidAcceptEx,sizeof(GuidAcceptEx),&lpfnAcceptEx,sizeof(lpfnAcceptEx),&dwbytes,NULL,NULL);

    recv_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(recv_sock == INVALID_SOCKET)
        printf("ERR LOG : RECV_SOCK ERROR \n");
    // return 1;

    memset(&Overapped,0,sizeof(Overapped));

    if(lpfnAcceptEx(listen_sock,recv_sock,acceptbuff,ACCEPT_BUFF_SIZE-((sizeof (struct sockaddr_in) + 16) * 2),sizeof (struct sockaddr_in) + 16, sizeof (struct sockaddr_in) + 16,&dwbytes,&Overapped))
    {
        printf("ERR LOG : acceptex failed  [ %u ]\n",WSAGetLastError());
        closesocket(listen_sock);
        closesocket(recv_sock);
        return 1;
    }

    

    hcompPort1 = CreateIoCompletionPort((HANDLE) recv_sock, hcompPort, (u_long) 0, 0);
    if(hcompPort1 ==NULL)
        printf("ERR LOG : CreateIOcompletionPort failed \n");

    PSOCKADDR pLocalSocketAddr = NULL;
    PSOCKADDR pRemoteSocketAddr=NULL;
    int pRemoteSocketAddrLength = 0;
    int pLocalSocketAddrLength = 0;
    printf("[INETADDR] : %s",buffer);
    lpfnGetAcceptExSockaddrs(buffer,(MAX_BUFFSIZE-((sizeof(SOCKADDR_IN) + 16) * 2)),sizeof(SOCKADDR_IN) + 16,sizeof(SOCKADDR_IN) + 16,pLocalSocketAddr,pLocalSocketAddrLength,pLocalSocketAddrLength,pRemoteSocketAddrLength);
    printf("==================================================================\n");
    SOCKADDR_IN *remoteaddr = (SOCKADDR_IN*) pRemoteSocketAddr;
   
}