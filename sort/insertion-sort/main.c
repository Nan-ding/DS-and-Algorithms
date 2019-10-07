#include "insertion_sort.c"
#include <stdio.h>

// test for int
int cmp(node *n1, node *n2) {
    return *(int *)(n1->data) - *(int *)(n2->data);
}

int main() {
    int arr[] = {9, 8, 7, 6, 5, 4};
    int i;
    node *head = (node *)malloc(sizeof(node) * 6);
    for (i = 0; i<6; ++i) {
        head[i].data = malloc(sizeof(int));
        *(int*)head[i].data = arr[i];
    }
    sort(head, 6, cmp, ASC);
    // printf
    for (i = 0; i<6; ++i) {
        printf("%d\n", *(int*)head[i].data);
    }
    // destory
    for (i = 0; i<6; ++i) {
        free(head[i].data);
    }
    free(head);
    return 0;
}