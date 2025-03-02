// Author: Gabrielle Stewart
// feb 2025
// This program implements a binary search tree.
#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

static struct tree_node* createNode(const char* name) {
    struct tree_node* newNode = (struct tree_node*)malloc(sizeof(struct tree_node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newNode->data.name, name, 64);
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct tree_node* insert(const char* name, struct tree_node* root) {
    if (root == NULL) return createNode(name);

    if (strcmp(name, root->data.name) < 0)
        root->left = insert(name, root->left);
    else if (strcmp(name, root->data.name) > 0)
        root->right = insert(name, root->right);

    return root;
}

struct tree_node* find(const char* name, struct tree_node* root) {
    if (root == NULL || strcmp(name, root->data.name) == 0) return root;

    if (strcmp(name, root->data.name) < 0)
        return find(name, root->left);
    else
        return find(name, root->right);
}

void clear(struct tree_node* root) {
    if (root == NULL) return;
    clear(root->left);
    clear(root->right);
    free(root);
}

void printHelper(struct tree_node* root, int depth) {
    if (root == NULL) return;

    for (int i = 0; i < depth; i++) printf(" ");
    printf("%s\n", root->data.name);

    printHelper(root->left, depth + 1);
    printHelper(root->right, depth + 1);
}

void print(struct tree_node* root) {
    printHelper(root, 0);
}

void printSorted(struct tree_node* root) {
    if (root == NULL) return;
    printSorted(root->left);
    printf("%s\n", root->data.name);
    printSorted(root->right);
}

