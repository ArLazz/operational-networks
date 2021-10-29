#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree{
    int key;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} node;

node *add(node *root, int key){
    node *root2 = root, *root3 = NULL;
    node *tmp = malloc(sizeof(node));
    tmp -> key = key;
    while (root2 != NULL){
        root3 = root2;
        if (key < root2 -> key) {
            root2 = root2->left;
        } else {
            root2 = root2->right;
        }
    }
    tmp -> parent = root3;
    tmp -> left = NULL;
    tmp -> right = NULL;
    if (key < root3 -> key)
        root3 -> left = tmp;
    else
        root3 -> right = tmp;
    return root;
}

int findelem(node *root, int key){
    if (root == 0)
        return -2147483648;
   if (root -> key == key)
        return 0;
    return 1 + findelem(((root -> key > key) ? root -> left : root -> right), key);
}
void outputtree(node *root){
    if (root == NULL)
        return;
    if (root -> key)
        printf("%d ", root -> key);
    outputtree(root -> left);
    outputtree(root -> right);
}
void deletetree(node *root){
    if (root){
        deletetree((root-> left));
        deletetree((root -> right));
        free(root);
        root = NULL;
    }
}
int main(){
    int a, n;
    printf("Введите элементы дерева(признак конца ввода 0):\n");
    scanf("%d", &a);
    node *root = malloc(sizeof(node)), *startroot;
    startroot = root;
    root -> key = a;
    root -> parent = NULL;
    root -> left = NULL;
    root -> right = NULL;
    scanf("%d", &a);
    while (a != 0){
        add(root, a);
        scanf("%d", &a);
    }
    printf("Обход дерева в прямом порядке:\n");
    outputtree(root);
    printf("\n");
    printf("Какой элемент надо найти?\n");
    scanf("%d", &a);
    n = findelem(root, a);
    printf("Длина пути(количество узлов)(если не входит то -1).\n");
    if (n < 0) n = -1;
    printf("%d", n);
    deletetree(root);
    printf("\n");
}