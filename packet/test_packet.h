#ifndef TEST_PACKET_H
    #define TEST_PACKET_H
#endif

#include "../buffer/buffer.h"
#include "test.h"

typedef struct s_test
{
    int usrid;
    char *chat_buff;
}s_test;

short get_protocol();
void s_test_read_packet(BUFFER *buff);
void s_test_write_packet(BUFFER *buff);
