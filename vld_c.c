#include"hash_table.h"
#include"vld_c.h"

void* __malloc(size_t sz, const char* file, size_t line)
{
    void *result;
    size_t total_size = sizeof(MemNode) + sz;
    MemNode *p = create_node(total_size);
    fill_node(p, sz, file, line);
    link_node(p);
    result = p+1;
    return result;
}

void __free(void *ptr)
{
    Pair pr = find_node(ptr);
    if(pr.prev==NULL && pr.cur==NULL)
    {
        printf("%p delete is invalid.\n");
        return;
    }
    
    MemNode *p = pr.cur;
    size_t index = Hash(ptr);
    //删除节点位第一个节点
    if(pr.prev==pr.cur && pr.prev!=NULL)
        hash_table[index] = p->link;
    else
        pr.prev->link = p->link;
    
    free_node(p);
}

