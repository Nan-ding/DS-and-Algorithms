#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <stdlib.h>
#include <stdio.h>

// the left of node
#define LEFT    1
// the right of node
#define RIGHT   2

typedef struct node {
    void *data;
    struct node *l_child;
    struct node *r_child;
    struct node *parent;
    // -1 : node is root node
    // 1 : node is the l_child of the parent
    // 2 : node is the r_child of the parent
    int direction;
} node;

// if n1 > n2, please return a value greater than 0
// if n1 < n2, please return a value less than 0
typedef int (*compare) (void *, void *);
// printf the data of node
typedef void (*printfdata) (void *);
// destory the data of node
typedef void (*destorydata) (void *);

static int __check_the_status (node *);
static void __replace_node (node *, node *);

// initialize the node.
void initnode (node *n) {
    n->data = NULL;
    n->r_child = NULL;
    n->r_child = NULL;
    n->parent = NULL;
    n->direction = -1;
}

// initialize the node by some data.
void initnodebydata (node *n, void *data) {
    if (data == NULL)
        return;
    initnode(n);
    n->data = data;
}

// create the node contain the data.
// if the data is invaild, NULL will be returned.
node* createnode (void *data) {
    if (data == NULL)
        return NULL;
    node *tmp = (node *)malloc(sizeof(node));
    initnodebydata(tmp, data);
    return tmp;
}

// insert newnode into the tree.
// cmp is the function of compare.
int insertnode (node *root, node *newnode, compare cmp) {
    if (root == NULL ||  newnode == NULL || cmp == NULL)
        return 0;
    // find the insertion point
    node *point = NULL, *cur = root;
    while (cur != NULL) {
        if (cmp(cur->data, newnode->data) > 0) {
            // n1 > n2
            point = cur;
            cur = cur->l_child;
        } else {
            // n1 <= n2
            point = cur;
            cur = cur->r_child;
        }
    }
    if (point == NULL)
        point = root;
    // choose the direction
    if (cmp(point->data, newnode->data) > 0) {
        point->l_child = newnode;
        newnode->parent = point;
        newnode->direction = LEFT;
    } else {
        point->r_child = newnode;
        newnode->parent = point;
        newnode->direction = RIGHT;
    }
    return 1;
}

// insert data into the tree.
// call insertnode actually.
int insertnodebydata (node *root, void *data, compare cmp) {
    node *tmp = createnode(data);
    if (tmp == NULL)
        return 0;
    return insertnode(root, tmp, cmp);
}

node *find (node *root, void *data, compare cmp);

// delete node from the tree.
// the value returned was contained in the node. please destroy it yourself.
// The data to be deleted may be the root nodd, so the second level pointer is introduced.
void* deletedata (node **root, void *data, compare cmp) {
    if (*root == NULL ||  data == NULL || cmp == NULL)
        return NULL;
    node *point = NULL, *ret = NULL;
    point = find(*root, data, cmp);
    if (point == NULL)
        return NULL;
    if (point == *root && (point->r_child == NULL || point->l_child == NULL)) {
        node *t = *root;
        if ((*root)->l_child == NULL && (*root)->r_child == NULL) {
            ret = (*root)->data;
            *root = NULL;
            free(t);
            return ret;
        } else if ((*root)->l_child != NULL && (*root)->r_child == NULL) {
            *root = t->l_child;
        } else if ((*root)->l_child == NULL && (*root)->r_child != NULL) {
            *root = t->r_child;
        }
        (*root)->parent = NULL;
        ret = t->data;
        free(t);
        return ret;
    }
    // check the status of delete action
    int status = __check_the_status(point);
    if (status == -1) {
        return NULL;
    } else if (status == 0) {
        if ((point->direction) & 1) {
            point->parent->l_child = NULL;
            ret = point->data;
            free(point);
            return ret;
        } else if ((point->direction) & 2) {
            point->parent->r_child = NULL;
            ret = point->data;
            free(point);
            return ret;
        }
    } else if (status == 1) {
        __replace_node(point, point->l_child);
        ret = point->data;
        free(point);
        return ret;
    } else if (status == 2) {
        // maybe root is equal to the node
        if (point != *root)
            __replace_node(point, point->r_child);
        point->r_child->l_child = point->l_child;
        if (point->l_child != NULL)
            point->l_child->parent = point->r_child;
        // maybe root is equal to the node
        if (point == *root) {
            *root = point->r_child;
            (*root)->parent = NULL;
        }
        ret = point->data;
        free(point);
        return ret;
    } else if (status == 3) {
        node *rchild = point->r_child;
        // find the leftmost node
        node *left = rchild->l_child;
        while (left->l_child != NULL) {
            left = left->l_child;
        }
        left->parent->l_child = left->r_child;
        if (left->r_child != NULL)
            left->r_child->parent = left->parent;
        // exchange the nodes
        // maybe root is equal to the node
        if (point != *root)
            __replace_node(point, left);
        left->l_child = point->l_child;
        left->r_child = point->r_child;
        if (point->l_child != NULL)
            point->l_child->parent = left;
        if (point->r_child != NULL)
            point->r_child->parent = left;
        // maybe root is equal to the node
        if (point == *root) {
            *root = left;
            (*root)->parent = NULL;
        }
        ret = point->data;
        free(point);
        return ret;
    }
    return NULL;
}

// call deletedata actually
void* deletenode (node **root, node *delnode, compare cmp) {
    return deletedata(root, delnode->data, cmp);
}

// used by delete.
// -1 : root is invaild.
// 0 : root is the leaf of tree.
// 1 : root has no r_child.
// 2 : r_child of root has no l_child.
// 3 : r_child of root has l_child.
static int __check_the_status (node *root) {
    if (root == NULL)
        return -1;
    if (root->r_child == NULL && root->l_child == NULL)
        return 0;
    if (root->r_child == NULL)
        return 1;
    if (root->r_child->l_child == NULL)
        return 2;
    else
        return 3;
    return -1;
}

// replace the node.
static void __replace_node (node *replaced, node *new) {
    if ((replaced->direction) & 1) {
        replaced->parent->l_child = new;
    } else if ((replaced->direction) & 2) {
        replaced->parent->r_child = new;
    }
    new->parent = replaced->parent;
}

// find the node.
node *find (node *root, void *data, compare cmp) {
    if (root == NULL || data == NULL || cmp == NULL)
        return NULL;
    // the point
    node *point = root;
    while (point != NULL) {
        if (cmp(point->data, data) > 0) {
            point = point->l_child;
        } else if (cmp(point->data, data) < 0) {
            point = point->r_child;
        } else {
            return point;
        }
    }
    return NULL;
}

// traversal the tree by pre-order.
void preordertraversal (node *root, printfdata pd) {
    if (root == NULL)
        return ;
    pd(root->data);
    preordertraversal(root->l_child, pd);
    preordertraversal(root->r_child, pd);
}

// destory the tree and free the space of data.
void destorytree (node *root, destorydata deldata) {
    if (root == NULL || deldata == NULL)
        return ;
    destorytree(root->l_child, deldata);
    destorytree(root->r_child, deldata);
    deldata(root->data);
    free(root);
}

#endif