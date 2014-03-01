#include "rb.h"

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
static void left_rotate(struct rb_t *tree,struct rb_node_t *pivot)
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
static void right_rotate(struct rb_t *tree,struct rb_node_t *pivote)
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
static struct rb_node_t *grand_parent(struct rb_node_t *node)
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
static struct rb_node_t *uncle(struct rb_node_t *node)
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
static void tree_insert(struct rb_t *tree,struct rb_node_t *node)
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
            tree->free(sub_root);
            return;
        }
    }
    /*Tree is Empty*/
    tree->root = node;
    node->parent = NULL;
    node->left  = NULL;
    node->right = NULL;
    node->colour = RED;
    return;
}

/*
 * Insert Fixup 
 *
 */
void rb_insert(struct rb_t *tree,struct rb_node_t *node)
{
    tree_insert(tree,node); 
    while(node->parent->colour == RED) {
        if(node->parent == node->parent->parent->left) {
            struct rb_node_t *y = uncle(node);
            if(y->colour == RED) {
                node->parent->colour = BLACK;
                y->colour = BLACK;
                node->parent->parent->colour = RED;
                node = node->parent->parent;
            } else if(node == node->parent->right) {
               node = node->parent;
               left_rotate(tree,node);
               node->parent->colour = BLACK;
               node->parent->parent->colour = RED;
               right_rotate(tree,node->parent->parent);
            }
        } else {
            struct rb_node_t *y = uncle(node);
            if(y->colour == RED) {
                node->parent->colour = BLACK;
                y->colour = BLACK;
                node->parent->parent->colour = RED;
                node = node->parent->parent;
            } else if(node == node->parent->left) {
                node = node->parent;
                right_rotate(tree,node);
                node->parent->colour = BLACK;  
                node->parent->parent->colour = RED;
                left_rotate(tree,node->parent->parent);
            }
        }
    }    
}

/*
 * Inorder
 */
void rb_inorder(struct rb_t *tree,struct rb_node_t *node)
{
    if(node) {
        inorder(tree,node->left);
        printf("node=");
        tree->print(node);
        printf("node->left");
        tree->print(node->left);
        printf("node->right");
        tree->print(node->right);
        inorder(tree,node->right);
    }
}
