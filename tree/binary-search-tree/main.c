#include "binary_search_tree.c"

// test for int
int cmp (void *n1, void *n2) {
    if (n1 != NULL && n2 != NULL)
        return *(int *)n1 - *(int *)n2;
}

// test for int
void pd (void *data) {
    if (data != NULL)
        printf("%d\n", *(int *)data);
}

// test for int
void dd (void *data) {
    if (data != NULL)
        free(data);
}

// test
int main () {
    // initial the root
    int *tmp = (int *)malloc(sizeof(int));
    *tmp = 40;
    node *root = createnode(tmp);
    int i = 0, *tt;
    // the data to be inserted
    // int arr[] = {30, 70, 10, 35, 33, 37, 50, 90, 60 ,80};
    int arr[] = {30, 10, 35, 33, 37};
    if (root == NULL) {
        printf("invaild value of root\n");
        return 1;
    }
    // insert
    for (; i<5; ++i) {
        tmp = (int *)malloc(sizeof(int));
        *tmp = arr[i];
        insertnodebydata(root, tmp, cmp);
    }
    // traversal
    preordertraversal(root, pd);
    printf("------------\n------------\n");
    tmp = (int *)malloc(sizeof(int));
    *tmp = 40;
    // find data
    if (find(root, tmp, cmp)) {
        printf("find\n\n");
    } else {
        printf("no data\n\n");
    }
    // delete data
    tt = deletedata(&root, tmp, cmp);
    // free the space
    dd(tt);
    preordertraversal(root, pd);
    printf("------------\n------------\n");
    // find data
    if (find(root, tmp, cmp)) {
        printf("find\n\n");
    } else {
        printf("no data\n\n");
    }
    destorytree(root, dd);
    free(tmp);
    return 0;
}