#ifndef SELECTION_SORT
#define SELECTION_SORT

#include <stdlib.h>

#define DESC 0
#define ASC  1

typedef struct node {
    void *data;     // data of node
}node;

typedef int (*compare)(node *n1, node *n2);
void exchange(node *nodes, int first, int second);

// sort funciton
void sort(node *nodes, int size, compare cmp, int method) {
    int curi, curj;
    node *tmp = NULL;
    for (curi = 0; curi < size; ++curi) {
        tmp = &nodes[curi];
        for (curj = curi - 1; curj >= 0; --curj) {
            if (method == ASC) {
                if (cmp(tmp, &nodes[curj]) >= 0) {
                    //exchange(nodes, curj, curi);
                    break;
                }
            } else if (method == DESC) {
                if (cmp(tmp, &nodes[curj]) <= 0) {
                    //exchange(nodes, curj, curi);
                    break;
                }
            }
        }
        curj = curj < 0 ? 0 : curj + 1;
        // exchange the two nodes
        exchange(nodes, curj, curi);
    }
}

// exchange elements
void exchange(node *nodes, int first, int second) {
    void *tmp = NULL;
    int i;
    tmp = nodes[second].data;
    for (i = second; i > first; --i) {
        nodes[i].data = nodes[i-1].data;
    }
    nodes[first].data = tmp;
}

#endif