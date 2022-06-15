#ifndef HASHMAP_H
    #define HASHMAP_H
#endif
#include <stdint.h>
#include <stdlib.h>

#include "../SHA256/KISA_SHA256.h"

typedef unsigned char BYTE;
typedef unsigned int UINT;

struct BUCKET* hashtable = NULL;

typedef struct h_NODE
{
    struct h_NODE *next;
    struct h_NODE *prev;
    BYTE *key;
    BYTE *value;
}h_NODE;
typedef struct BUCKET
{
    struct h_NODE *head;
    struct h_NODE *tail;
    BYTE *hash;
    int count;
}BUCKET;

h_NODE *init_h_node(h_NODE *node);
void h_add(BUCKET *bucket,BYTE *key,char *data);



