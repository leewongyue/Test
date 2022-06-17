// #include <stdio.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <Windows.h>
// typedef struct h_NODE
// {
//     struct h_NODE *next;
//     uint32_t key;
//     void *value;
// }h_NODE;

// typedef struct HASHTABLE
// {
//     struct h_NODE *head;
//     uint32_t count;
// }HASHTABLE;

// uint32_t uint_hash(uint32_t a)
// {
//     a = (a+0x7ed55d16) + (a<<12);
//     a = (a^0xc761c23c) ^ (a>>19);
//     a = (a+0x165667b1) + (a<<5);
//     a = (a+0xd3a2646c) ^ (a<<9);
//     a = (a+0xfd7046c5) + (a<<3);
//     a = (a^0xb55a4f09) ^ (a>>16);
//     a= a >> 4;
//     return a;
// }

// int main()
// {

//     // for(int i=0; i<60000;i++)
//     // {
//     //     printf("[VALUE : %d] [HASH : %d]\n",i,uint_hash(i));
//     // }
//     printf("%d",sizeof(HASHTABLE));
//     HASHTABLE * table = malloc(sizeof(HASHTABLE)*3000000000);
//     h_NODE *node = malloc(sizeof(h_NODE));

//     uint32_t hashindex = uint_hash(2);
//      printf("[VALUE : %d] [HASH : %d]\n",1,hashindex);

//     printf("[TABLE]                     %p\n",table);
//     printf("[TABLE-> Head]              %p\n",table->head);
//     node->key = 1;
//     node->next = NULL;
//     node->value = "asdfg\0";
//     //uint32 범위 안의 hash 값의 인덱스에 접근시 오버플로우
//     printf("[TABLE[HASHINDEX]]         %p\n",table[hashindex]);
//     printf("[TABLE[HASHINDEX].head]    %p\n",table[hashindex].head);
//     // table[hashindex].head = malloc(sizeof(h_NODE));
//     printf("[TABLE[HASHINDEX].head]    %p\n",table[hashindex].head);
//     printf("[newnode]                  %p\n",node);
//     table[hashindex].head = node;
//     printf("[TABLE[HASHINDEX].head]    %p\n",table[hashindex].head);
//     printf("[TABLE-> Head]             %p\n",table->head);

    
//     table[hashindex].head = node;
//     // table->head = node;
//     table->count = 10;
//     printf("[TABLE-> Head]             %p\n",table->head);
//     printf("[TABLE-> Head]             %p\n",table[1].head);
//     printf("[TABLE cnt]                %d\n",table->count);
//     Sleep(10000);
//     free(table[hashindex].head);
//     free(table);
//     Sleep(10000);
// }