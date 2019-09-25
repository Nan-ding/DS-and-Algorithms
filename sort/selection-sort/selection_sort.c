#ifndef SELECTION_SORT
#define SELECTION_SORT

#include <stdlib.h>

#define DESC 0
#define ASC  1

typedef struct node {
    void *data;     // data of node
}node;

typedef int (*compare)(node *n1, node *n2);

// sort funciton
void sort(node *nodes, int size, compare cmp, int method) {
    int curi, curj;
    node *tmp = NULL;
    for (curi = 0; curi < size; ++curi) {
        tmp = &nodes[curi];
        for (curj = curi + 1; curj < size; ++curj) {
            if (method == ASC) {
                if (cmp(tmp, &nodes[curj]) >= 0)
                    tmp = &nodes[curj];
            } else if (method == DESC) {
                if (cmp(tmp, &nodes[curj]) <= 0)
                    tmp = &nodes[curj];
            }
        }
        // exchange the two nodes
        if (tmp != &nodes[curi]) {
            void *t = tmp->data;
            tmp->data = nodes[curi].data;
            nodes[curi].data = t;
        }
    }
}

#endif