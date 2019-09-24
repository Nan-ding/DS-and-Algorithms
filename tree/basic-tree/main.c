#include "b_tree.c"

int main () {
    node *root = (node *)malloc(sizeof(node));
    initnode(root);
    // insert some nodes;
    node *tmp = NULL;
//                     -1
//                    /    
//                   0
//                  / \
//                 1   2
//                    / \
//                   3   4
    tmp = insertdata(root, 0, LEFT);
    insertdata(tmp, 1, LEFT);
    tmp = insertdata(tmp, 2, RIGHT);
    insertdata(tmp, 3, LEFT);
    insertdata(tmp, 4, RIGHT);
    // pre-order
    preordertraversal(root);
    printf("------------\n------------\n");
    // in-order
    inordertraversal(root);
    printf("------------\n------------\n");
    // post-order
    postordertraversal(root);
    destorytree(root);
    return 0;
}