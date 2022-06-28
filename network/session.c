#include "session.h"

void init_session(SESSION *session)
{
    session = malloc(sizeof (SESSION));
    init_recvbuff(session->recvbuffer,MAX_RECVBUFF_SIZE);
    at_init_queue(session->sendqueue);
    session->disconnected = false;

}
void clear(atomic_QUEUE *queue)
{
    clear_queue(queue);
}
//완료 핸들러 관련해서 공부
void start(int socket);
void disconnect(int socket)
{
    shutdown(socket,SHUT_WR);
}
void send_buff(BUFFER* buffer,SESSION *session)
{
    at_enqueue(session->sendqueue,buffer);
    reg_send(session);
}
void reg_send(SESSION *session)
{
    if(session->disconnected == true)
        return;
    while (session->sendqueue->count > 0)
    {
        BUFFER *buff = (BUFFER*)at_peek(session->sendqueue);
        if(try_send(buff, session->session_socket,session))
        {
            DEBUG_ERR("REG_SEND failed",-1);
            continue;
        }
        else
        {
            at_dequeue(session->sendqueue);
            continue;
        }
    }
    send_completed(0,session->send_args);

}
bool try_send(BUFFER *bufer,int socket,SESSION *session)
{
    int transffered;
    int bufferlen = buffer_len(buffer);
    if((transffered = send(socket,buffer,bufferlen,MSG_DONTWAIT)) == -1)
    {
        DEBUG_ERR("send failed",transffered);
        return true;
    }
    else
    {
        session->send_args->bytetransferred += transffered;
        return false;
    }
}
void send_completed(void *sender,SESSION *session)
{
    if(session->send_args->bytetransferred > 0 && session->send_args->socketstate == STATE_ACCEPTED )
    {
        on_send(session->send_args->bytetransferred);
        session->send_args->bytetransferred = 0;
        if(session->sendqueue->count > 0)
            reg_send(session);
    }
    else
    {
        disconnect(session->session_socket);
        session->disconnected = true;
        clear(session->sendqueue);
        free(session);

    }
}
void reg_recv(SESSION *session)
{
    if(session->disconnected == true)
        return;
    clean_buffer(session->recvbuffer);
    BUFFER *buff = get_writebuffer(session->recvbuffer);

    if(try_recv(session))
    {
        return;
    }
    else
    {
        recv_completed(0,session);
    }
}
bool try_recv(SESSION *session)
{
    int bytetransferred;
    if((bytetransferred=recv(session->session_socket,session->recvbuffer->read_buffer->buffer,MAX_RECVBUFF_SIZE,MSG_DONTWAIT)) == -1)
    {
        DEBUG_ERR("RECV FAILED",-1);
        return true;
    }
    else
        session->recv_args->bytetransferred+=bytetransferred;
        return false;
}
void recv_complete(void *sender,SESSION *session)
{
    if(session->recv_args->bytetransferred > 0 && session->recv_args->socketstate == STATE_ACCEPTED)
    {
        if(onwrite_buffer(session->recv_args->bytetransferred,session->recvbuffer) == false)
        {
            disconnect(session->session_socket);
            session->disconnected = true;
            clear(session->sendqueue);
            free(session);
            return;
        }

        int processLen = on_recv(get_readbuffer(session->recvbuffer));
        if(processLen < 0 || get_datasize(session->recvbuffer) < processLen)
        {
            disconnect(session->session_socket);
            session->disconnected = true;
            clear(session->sendqueue);
            free(session);
            return;
        }
    }
}
