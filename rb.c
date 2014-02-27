#include <stdio.h>

/*
 * Data structure for a node in red black tree
 */
struct rb_node_t {
    enum {red,black} colour;
    void *key;
    void *data;
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
    uint32_t nelements;
};

/*
 *  Left Rotate operation
 *  root: root of the tree
 *  pivot: node at which tree should be rotated
 *           x*                y  
 *          / \               / \
 *         a   y    =>       x*   c 
 *            / \           / \
 *           b   c         a   b
 *
 */
void left_rotate(struct rb_t *tree,struct rb_node_t *pivot)
{
    struct rb_node_t *x = pivot;
    struct rb_node_t *y = x->right;
    x->right            = y->left;

    if(y->left != NULL) 
        y->left->parent = x;

    y->parent = x->parent; 
    if(x->parent) {
        if(x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
    } else tree->root = y;
    y->left = x;
    x->parent = y;
}

/*
 * Right Rotate Operation
 * tree: tree data Structure
 * pivot: node at which tree should be rotated
 *
 *         y            x*
 *        / \          / \
 *       x*  c  =>    a   y
 *      / \              / \
 *     a   b            b   c
 */
void right_rotate(struct rb_t *tree,struct rb_node_t *pivote)
{
    struct rb_node_t *x = pivote;
    struct rb_node_t *y = pivote->parent;
    y->left = x->right;
    if(x->right) x->right->parent = y;
    x->parent = y->parent;
    if(y->parent) {
        if(y->parent->left == y) y->parent->left = x;
        else y->parent->right = x;
    } else tree->root = x; 
    x->right = y;
    y->parent = x;
}

/*
 *                            G                     
 *                           / \.                     
 *                          U   P                
 *                             / \
 *                            N    N 
 * G => Grand Parent
 * U => Uncle
 * P => parent
 * N => Node
 */


/*
 * Find Grand parent of a node 
 * node : relative to this node
 */
struct rb_node_t *grand_parent(struct rb_node_t *node)
{
    if((node != NULL) && (node->parent != NULL)) {
        return node->parent->parent;
    }
    return NULL;
}

/*
 * Find Uncle of a node
 * node: relative to this node
 */
struct rb_node_t *uncle(struct rb_node_t *node)
{
    struct rb_node_t *g = grand_parent(node);
    if(g == NULL) return NULL;
    if(node->parent == g->left) return g->right;
    else return g->left;
}

/*
 * Insert Function
 * tree: tree data structure
 * node: new node to be inserted
 * result tree:
 *              X 
 *             / \
 *          a<X  b>X
 */
void tree_insert(struct rb_t *tree,struct rb_node_t *node)
{
    struct rb_node_t *root = tree->root;
    struct rb_node_t *sub_root = root;
    while(sub_root) {
        if(tree->com_fn(sub_root,node) > 0) {
            if(sub_root->right) {
                sub_root = sub_root->right;
            } else {
                sub_root->right = node;
                node->right = NULL;
                node->left  = NULL;
                node->parent = sub_root;
                node->colour = RED;
                break;
            }                
        } else if(tree->com_fn(sub_root,node) < 0) {
            if(sub_root->left) {
                sub_root = sub_root->left;
            } else {
                sub_root->left = node;
                node->left = NULL;
                node->right = NULL;
                node->parent = sub_root;
                node->colour = RED;
            }
        } else {
            //duplicate
            if(sub_root->parent->left == sub_root) {
                sub_root->parent->left = node;
            } else {
                sub_root->parent->right = node;
            }
            node->left = sub_root->left;
            node->right = sub_root->right;
            node->parent = sub_root->parent;
            node->colour = RED;
            free(sub_root);
            return;
        }
    }
    /*Tree is Empty*/
    tree->root = node;
    node->parent = NULL;
    node->left  = NULL;
    node->right = NULL;
    node->colour = BLACK;
    return;
}

/*
 * Insert Fix up
 */
void insert_fixup(
