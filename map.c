#include "rb.h"

struct map_node {
    void *key;
    void *value;
    struct rb_node_t rbnode;
};

typedef struct rb_t map_t;

static int map_compare(struct rb_node_t *node1,struct rb_node_t *node2)
{
    struct map_node *map_node1 = (struct map_node *)((char *)node1 - ((size_t)&(((struct map_node *)0)->rbnode)));
    struct map_node *map_node2 = (struct map_node *)((char *)node2 - ((size_t)&(((struct map_node *)0)->rbnode)));
    printf("node address is %u %u\n",map_node1,map_node2);
    return strncmp((char *)(map_node1->key),(char *)(map_node2->key),100);
}

static void map_free(struct rb_node_t *node)
{
    struct map_node *map_node = (struct map_node *)((char *)node - ((size_t)&(((struct map_node *)0)->rbnode)));
    free(map_node);
}

static void map_print(struct rb_node_t *node)
{
    struct map_node *map_node = (struct map_node *)((char *)node - ((size_t) & (((struct map_node *)0)->rbnode)));
    printf("Key=%s,Value=%s\n",(char *)map_node->key,(char *)map_node->value);
}

map_t *map_init()
{
    map_t *map_root  = (map_t *)malloc(sizeof(map_t));
    map_root->root   = NULL;
    map_root->com_fn = map_compare;
    map_root->free   = map_free;
    map_root->print  = map_print;
}

int map_insert(map_t *map_root,void *key,void *value)
{
    struct map_node *node = (struct map_node *)malloc(sizeof(struct map_node));
    printf("node address is %u\n",node);
    node->key   = key;
    node->value = value;
    rb_insert((struct rb_t *)map_root,&(node->rbnode));
    return 1;
}

int main(int argc,char *argv[])
{
    map_t *map = map_init();
    printf("Starting insetion \n");
    map_insert(map, "a"   ,"z");
    rb_inorder(map,map->root);
    rb_preorder(map,map->root);
    printf("**************");
    map_insert(map, "b","y");
    rb_inorder(map,map->root);
    rb_preorder(map,map->root);
    printf("**************");
    map_insert(map, "c" ,"x");
    rb_inorder(map,map->root);
    rb_preorder(map,map->root);
    printf("**************");
    map_insert(map, "d" ,"w");
    rb_inorder(map,map->root);
    rb_preorder(map,map->root);
    printf("**************");
    map_insert(map, "e"   ,"v");
    rb_inorder(map,map->root);
    rb_preorder(map,map->root);
    printf("**************");
}
