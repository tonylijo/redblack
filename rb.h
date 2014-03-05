#ifndef _REDBLACK_H__
#define _REDBLACK_H__

#include <stdio.h>
#include <stdlib.h>
typedef enum{RED,BLACK} rb_colour_t;
/*
 * Data structure for a node in red black tree
 */
struct rb_node_t {
    rb_colour_t colour;
    struct rb_node_t *left;
    struct rb_node_t *right;
    struct rb_node_t *parent;
};

/*
 * Root element datastructure
 */
struct rb_t {
    struct rb_node_t *root;
    int (*com_fn)(struct rb_node_t *node1,struct rb_node_t *node2);
    void (*free)(struct rb_node_t *node);
    void (*print)(struct rb_node_t *node);
};

void rb_insert(struct rb_t *tree,struct rb_node_t *node);
void rb_inorder(struct rb_t *tree,struct rb_node_t *node);
void rb_preorder(struct rb_t *tree,struct rb_node_t *node);
#endif
