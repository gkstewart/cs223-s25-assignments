// Author: Gabby Stewart
// feb 2025
// This program builds a binary search tree of a given set of files.
#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAX_LINE 256

struct file_node {
    char filename[128];
    struct tree_node* dependencies;
    struct file_node* left;
    struct file_node* right;
};

static struct file_node* createFileNode(const char* filename) {
    struct file_node* newNode = (struct file_node*)malloc(sizeof(struct file_node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newNode->filename, filename, 128);
    newNode->dependencies = NULL;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct file_node* insertFile(struct file_node* root, const char* filename) {
    if (root == NULL) return createFileNode(filename);
    
    if (strcmp(filename, root->filename) < 0)
        root->left = insertFile(root->left, filename);
    else if (strcmp(filename, root->filename) > 0)
        root->right = insertFile(root->right, filename);
    
    return root;
}

struct file_node* findFile(struct file_node* root, const char* filename) {
    if (root == NULL || strcmp(filename, root->filename) == 0) return root;
    
    if (strcmp(filename, root->filename) < 0)
        return findFile(root->left, filename);
    else
        return findFile(root->right, filename);
}

void parseFileDependencies(struct file_node* fileNode) {
    FILE* file = fopen(fileNode->filename, "r");
    if (!file) {
        fprintf(stderr, "Cannot open file: %s\n", fileNode->filename);
        return;
    }
    
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, file)) {
        if (strstr(line, "#include")) {
            char* start = strchr(line, '"');
            if (start) {
                char* end = strchr(start + 1, '"');
                if (end) {
                    *end = '\0';
                    fileNode->dependencies = insert(start + 1, fileNode->dependencies);
                }
            }
        }
    }
    fclose(file);
}

void listFiles(struct file_node* root) {
    if (root == NULL) return;
    listFiles(root->left);
    printf("%s\n", root->filename);
    listFiles(root->right);
}

void printDependencies(struct tree_node* root) {
    if (root == NULL) return;
    printDependencies(root->left);
    printf("  %s\n", root->data.name);
    printDependencies(root->right);
}

void commandLoop(struct file_node* root) {
    char input[128];
    while (1) {
        printf("$ ");
        if (!fgets(input, sizeof(input), stdin)) break;
        
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "quit") == 0) break;
        if (strcmp(input, "list") == 0) {
            listFiles(root);
            continue;
        }
        
        struct file_node* file = findFile(root, input);
        if (!file) {
            printf("%s not found\n", input);
        } else {
            printf("%s has the following dependencies\n", input);
            printDependencies(file->dependencies);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }
    
    struct file_node* root = NULL;
    for (int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file) {
            fclose(file);
            root = insertFile(root, argv[i]);
        }
    }
    
    printf("Processing %d files\n", argc - 1);
    
    struct file_node* temp = root;
    while (temp) {
        parseFileDependencies(temp);
        temp = temp->right;
    }
    
    commandLoop(root);
    return 0;
}

