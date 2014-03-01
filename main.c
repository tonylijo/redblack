#include "rb.h"

struct map_node {
    void *key;
    void *value;
    struct rb_node_t rbnode;
};

struct map_t {
    struct map_node *root;
    int (*compare)(void *key1,void *key2);
    void(*free)(struct map_node *node);
};

int compare(struct rb_node_t *node1,struct rb_node_t *node2,void *data)
{
    struct map *map_node1 = (struct map *)((char *)node1 - ((size_t)&((struct map *)0)->rbnode));
    struct map *map_node2 = (struct map *)((char *)node2 - ((size_t)&((struct map *)0)->rbnode));
    return ((struct map_t *)data)->compare((char *)map_node1->key,(char *)map_node2->key);
}

void map_node_free(struct rb_node_t *node,void *data)
{
    struct map *map_node = (struct map *)((char *)node -((size_t)&((struct map *)0)->rbnode));
    if(
    free(map_node->key);
    free(map_node->value);
    free(map_node);
}

void print(struct rb_node_t *node,void *data)
{
    struct map *map_node = (struct map *)((char *)node -((size_t)&((struct map *)0)->rbnode));
    printf("node->key=%s node->value=%s\n",(char *)map_node->key,(char *)map_node->value);
    return;
}


int main(int argc,char *argv[])
{

    struct rb_t redblack = {
        .root   = NULL,
        .com_fn = compare,
        .free   = map_node_free,
        .print  = print
    };
    rb_insert(redblack,)    
}
