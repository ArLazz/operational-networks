#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree{
    char* key;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} node;

typedef struct N1 {
    char mychar;
    struct N1 *next;
} l1;
typedef struct N {
    char *c;
    struct N *next;
    struct N *prev;
} l2;

l1 *plus1(l1 *lst) {
    l1 *t;
    t = (struct N1 *) malloc(sizeof(l1));
    lst->next = t;
    t->next = NULL;
    return (t);
}
l2 *plus2(l2 *lst) {
    l2 *t;
    t = (struct N *) malloc(sizeof(l2));
    lst->next = t;
    t->prev = lst;
    t->next = NULL;
    return (t);
}
node *add(node *root, char *key){
    node *root2 = root, *root3 = NULL;
    node *tmp = malloc(sizeof(node));
    tmp -> key = key;
    while (root2 != NULL){
        root3 = root2;
        if (strcmp(key, root2 -> key) < 0) {
            root2 = root2->left;
        } else {
            root2 = root2->right;
        }
    }
    tmp -> parent = root3;
    tmp -> left = NULL;
    tmp -> right = NULL;
    if (strcmp(key, root3 -> key) < 0)
        root3 -> left = tmp;
    else
        root3 -> right = tmp;
    return root;
}
void buildtree(node *root,l2 *list){
    while (list ->next != NULL){
        printf("%s ", list -> c);
        root = add(root, list -> c);
        list = list -> next;
    }
    printf("\n");
}

void outputtree(node *root){
    if (root == NULL)
        return;
    if (root -> key)
        printf("%s ", root -> key);
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

int main(void) {
    l1 *t1, *st1, *pt1;
    l2 *p2, *l2, *st2, *end2;
    char q, *b;
    int i = 0, k = 1, z = 1, w = 0, j;
    st1 = (struct N1 *) malloc(sizeof(l1));
    t1 = st1;
    st2 = (struct N *) malloc(sizeof(l2));
    st2->prev = NULL;
    l2 = st2;
    printf("Последовательность слов:\n");
    q = getchar();
    while (q != EOF && q != '\n') {
        if (q != ' ') {
            if (z == 1) {
                i = 0;
                z = 0;
            }
            pt1 = plus1(t1);
            t1 = t1->next;
            t1->mychar = q;
            i += 1;
            w = 1;
        } else {
            if (i != 0) {
                t1 = st1;
                j = 0;
                b = (char *) malloc(sizeof(char) * (i));
                while (t1 != NULL) {
                    *(b + j) = t1->mychar;
                    j += 1;
                    pt1 = t1;
                    t1 = t1->next;
                    free(pt1);
                }
                *(b + j) = '\0';
                p2 = plus2(l2);
                l2->c = b + 1;
                l2 = l2->next;
                st1 = (struct N1 *) malloc(sizeof(l1));
                t1 = st1;
            }
            z = 1;
            w = 0;
            i = 0;
        }
        q = getchar();
    }

    if (i != 0) {
        t1 = st1;
        j = 0;
        b = (char *) malloc(sizeof(char) * i);
        while (t1 != NULL) {
            *(b + j) = t1->mychar;
            j++;
            t1 = t1->next;
        }
        *(b + j) = '\0';
        l2->c = b + 1;
    }
    if (l2->c == NULL) {
        end2 = l2;
    } else {
        end2 = plus2(l2);
    }
    node *root = malloc(sizeof(node)), *startroot;
    startroot = root;
    root -> key = st2 -> c;
    root -> parent = NULL;
    root -> left = NULL;
    root -> right = NULL;
    l2 = st2 ->next;
    buildtree(root, l2);
    printf("Обход дерева в прямом порядке:\n");
    outputtree(root);
    deletetree(root);
    printf("\n");
}
