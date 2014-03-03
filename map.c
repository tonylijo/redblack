#include "rb.h"

struct map_node {
    void *key;
    void *value;
    struct rb_node_t rbnode;
};

typedef int  (*map_cmp_t)(void *,void *);
typedef void (*map_free_t)(void *,void *);
typedef void (*map_print_t)(void *,void *);

struct map_t {
    struct map_node *root;
    int (*compare)(void *key1,void *key2);
    void(*free)(void *key,void *value);
    void(*print)(void *key,void *value);
};

static int rb_compare(struct rb_node_t *node1,struct rb_node_t *node2,void *data)
{
    struct map *map_node1 = (struct map_node *)((char *)node1 - ((size_t)&((struct map *)0)->rbnode));
    struct map *map_node2 = (struct map_node *)((char *)node2 - ((size_t)&((struct map *)0)->rbnode));
    return ((struct map_t *)data)->compare((char *)map_node1->key,(char *)map_node2->key);
}

static void rb_free(struct rb_node_t *node,void *data)
{
    struct map_node *map_node = (struct map *)((char *)node -((size_t)&((struct map *)0)->rbnode));
    if(((struct map_t *)data)->free) {
        ((struct map_t *)data)->free(map_node->key,map_node->value);
    }
    free(map_node);
}

static void print(struct rb_node_t *node,void *data)
{
    struct map_node *map_node = (struct map_node *)((char *)node -((size_t)&((struct map *)0)->rbnode));
    ((struct map_t *)data)->print(map_node->key,map_node->value);
}

static inline struct map_node *create_node(void)
{
    struct map_node *node = (struct map_node *) malloc(sizeof(struct map_node));
    return node;
}

struct map_t *create_map(map_cmp_t cmp_func,map_free_t free_func,map_print_t print_func)
{
    struct map_t *map = (struct map_t *) malloc(sizeof(struct map_t));
    if(map) {
        map->root    = NULL;
        map->compare = cmp_func;
        map->free    = free_func;
        map->print   = print_func;
    }
    return map;
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
