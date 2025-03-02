// Author: Gabrielle Stewart
// feb 2025
// program that  takes a C file as a command line argument and uses a stack to check for matched braces.
#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    int line, column;
    struct StackNode *next;
} StackNode;

void push(StackNode **top, int line, int column) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->line = line;
    newNode->column = column;
    newNode->next = *top;
    *top = newNode;
}

int pop(StackNode **top, int *line, int *column) {
    if (*top == NULL) return 0;
    StackNode *temp = *top;
    *line = temp->line;
    *column = temp->column;
    *top = temp->next;
    free(temp);
    return 1;
}

void clear(StackNode **top) {
    StackNode *temp;
    while (*top) {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: ./match_braces <filename>\n");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Cannot open file: %s\n", argv[1]);
        return 1;
    }
    
    StackNode *stack = NULL;
    int line = 1, column = 0;
    int ch;
    
    while ((ch = fgetc(file)) != EOF) {
        column++;
        if (ch == '\n') {
            line++;
            column = 0;
        } else if (ch == '{') {
            push(&stack, line, column);
        } else if (ch == '}') {
            int matchLine, matchColumn;
            if (pop(&stack, &matchLine, &matchColumn)) {
                printf("Found matching braces: (%d, %d) -> (%d, %d)\n", matchLine, matchColumn, line, column);
            } else {
                printf("Unmatched brace on Line %d and Column %d\n", line, column);
            }
        }
    }
    
    while (stack) {
        printf("Unmatched brace on Line %d and Column %d\n", stack->line, stack->column);
        pop(&stack, &line, &column);
    }
    
    fclose(file);
    return 0;
}

