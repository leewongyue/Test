#ifndef HASHTABLE_H
    #define HASHTALE_H
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


typedef struct ch_NODE
{
    struct ch_NODE *next;
    uint32_t key;
    void *value;
}ch_NODE;
typedef struct C_HASHTABLE
{
    struct ch_NODE *head;
    uint32_t count;
    int col_cnt;
}C_HASHTABLE;

ch_NODE   *init_ch_node(ch_NODE *node);
C_HASHTABLE   *init_c_hashtable(C_HASHTABLE *bucket);
void     ch_add(C_HASHTABLE *bucket,uint32_t key,void *value);
uint32_t c_uint_hash(uint32_t x);
void     c_delete_key(C_HASHTABLE *table,uint32_t key);
void     *c_search_key(C_HASHTABLE *table,uint32_t key);
void     c_print_map(C_HASHTABLE *table);
