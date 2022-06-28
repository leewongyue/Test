#include "../network/listener.h"

int main___()
{
    struct sockaddr_in addr;
    SOCKETARGS *args = (SOCKETARGS*)malloc(sizeof (SOCKETARGS));
    init_socket(addr,args,3000);
}
