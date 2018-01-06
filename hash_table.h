#pragma once

#include<malloc.h>
#include<stdio.h>
#include<assert.h>

typedef struct MemNode
{
    const char *pfile;
    size_t line;
    size_t size;
    struct MemNode *link;
}MemNode;

typedef struct Pair
{
    MemNode *prev;
    MemNode *cur;
}Pair;

#define UL unsigned long
#define HASH_TABLE_SIZE 389
MemNode* hash_table[HASH_TABLE_SIZE] = {0};

MemNode* create_node(size_t sz)
{
    MemNode *p = (MemNode*)malloc(sz);
    assert(p != NULL);
    return p;
}
void free_node(MemNode *p)
{
    free(p);
    p = NULL;
}
void fill_node(MemNode *n, size_t sz, const char *file, size_t line)
{
    n->pfile = file;
    n->line = line;
    n->size = sz;
    n->link = NULL;
}
size_t Hash(void *p)
{
    return ((UL)p) % HASH_TABLE_SIZE;
}

void link_node(MemNode *n)
{
    size_t index = Hash(n+1);
    if(hash_table[index] == NULL)
        hash_table[index] = n ;
    else
    {
        n->link = hash_table[index];
        hash_table[index] = n;
    }
}

Pair find_node(void *ptr)
{
    Pair pr;
    size_t index = Hash(ptr);
    if(hash_table[index] == 0)
    {
        pr.prev = NULL;
        pr.cur = NULL;
    }
    else
    {
        MemNode *p = hash_table[index];
        //处理第一个节点
        if(p+1 == ptr)
        {
            pr.prev = p;
            pr.cur = p;
            return pr;
        }

        pr.prev = p;
        p = p->link;
        pr.cur = p;

        while(p != NULL)
        {
            if(p+1 == ptr)
                break;
            pr.prev = p;
            p = p->link;
            pr.cur  = p;
        }

        if(p == NULL)
        {
            pr.prev = NULL;
            pr.cur = NULL;
        }
    }
    return pr;
}

void check_leak()
{
    MemNode *p = NULL;
    int count = 0;
    int flag = 0;
    int i;
    for(i=0; i<HASH_TABLE_SIZE; ++i)
    {
        p = hash_table[i];
        if(p == NULL)
        {
            flag++;
            continue;
        }

        while(p != NULL)
        {
            count++;
            printf("[ERROR %d] at %p memleak,size: %d,file: %s, line %d\n",
                    count, p+1,p->size,p->pfile, p->line);
            p = p->link;
        }
    } 
    if(flag == HASH_TABLE_SIZE)
        printf("[OK] No Memory Leak.\n");
}

