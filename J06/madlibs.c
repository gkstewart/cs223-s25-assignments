//Gabby 4/22
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ADJ_LEN 32

int main() {
    char bool_input[6];
    int message;
    int num_adjectives;

    printf("boolean: ");
    scanf("%5s", bool_input);

    message = (strcmp(bool_input, "yes") == 0 || strcmp(bool_input, "Yes") == 0);

    printf("number:");
    scanf("%d", &num_adjectives);

    // memory for adjectives
    char **adjectives = (char **)malloc(num_adjectives * sizeof(char *));
    if (adjectives == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < num_adjectives; i++) {
        adjectives[i] = (char *)malloc(MAX_ADJ_LEN);
        if (adjectives[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }

        printf("adjective: ");
        scanf("%31s", adjectives[i]);
    }

    // sentence w/ adjectives in reverse order
    printf("You are the most");
    for (int i = num_adjectives - 1; i >= 0; i--) {
        printf(" %s", adjectives[i]);
    }
    printf(" and delightful person I know it's true\n");

    // free
    for (int i = 0; i < num_adjectives; i++) {
        free(adjectives[i]);
    }
    free(adjectives);

    return 0;
}
