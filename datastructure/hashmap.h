#ifndef HASHMAP_H
    #define HASHMAP_H
#endif

#include <stdlib.h>
#include <stdio.h>

#define MAX_BUCKET UINT32_MAX

typedef struct h_NODE
{
    struct h_NODE *next;
    uint32_t *key;
    void *value;
}h_NODE;
typedef struct HASHTABLE
{
    struct h_NODE *head;
    int count;
}HASHTABLE;

h_NODE   *init_h_node(h_NODE *node);
HASHTABLE   *init_hashtable(HASHTABLE *bucket);
void     h_add(HASHTABLE *bucket,uint32_t *key,void *value);
uint32_t uint_hash(uint32_t x);
void     delete_key(HASHTABLE *table,uint32_t key);
void     search(HASHTABLE *table,uint32_t key);
void     print_map(HASHTABLE *table);
