#ifndef B_TREE_H
#define B_TREE_H

#include <stdlib.h>
#include <stdio.h>

#define LEFT 0
#define RIGHT 1

// struct of binary tree.
typedef struct node {
    int data;                 // data of node
    struct node *l_child;       // left child of node
    struct node *r_child;       // right child of node
    struct node *parent;         // parent of node
} node;

// initialize node.
void initnode (node *root) {
    if (root == NULL)
        return ;
    root->data = -1;
    root->l_child = NULL;
    root->r_child = NULL;
    root->parent = NULL;
}

// insert the node into tree.
int insertnode (node *parent, node *newnode, int direction) {
    if (parent == NULL || newnode == NULL)
        return 0;
    if (direction != LEFT && direction != RIGHT)
        return 0;
    if (direction == LEFT) {
        parent->l_child = newnode;
        newnode->parent = parent;
    }
    else if (direction == RIGHT) {
        parent->r_child = newnode;
        newnode->parent = parent;
    }
    return 1;
}

// insert node initialed by data into tree.
// call insertnode actually.
node* insertdata (node *parent, int data, int direction) {
    node *tmp = (node *)malloc(sizeof(node));
    int ret;
    initnode(tmp);
    tmp->data = data;
    // actual insert
    ret = insertnode(parent, tmp, direction);
    if (ret == 0) {
        free(tmp);
        return NULL;
    }
    return tmp;
}

// traversal the tree by pre-order
void preordertraversal (node *root) {
    if (root == NULL)
        return;
    printf("%d\n", root->data);
    preordertraversal(root->l_child);
    preordertraversal(root->r_child);
}

// traversal the tree by in-order
void inordertraversal (node *root) {
    if (root == NULL)
        return;
    inordertraversal(root->l_child);
    printf("%d\n", root->data);
    inordertraversal(root->r_child);
}

// traversal the tree by post-order
void postordertraversal (node *root) {
    if (root == NULL)
        return;
    postordertraversal(root->l_child);
    postordertraversal(root->r_child);
    printf("%d\n", root->data);
}

// destory the tree
int destorytree (node *root) {
    if (root == NULL)
        return 0;
    destorytree(root->l_child);
    destorytree(root->r_child);
    free(root);
    return 1;
}

#endif