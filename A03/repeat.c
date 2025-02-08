/*----------------------------------------------
 * Author: Gabby Stewart 
 * Date: February 2025
 * Description: Repeating program that takes a user input 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 32

int main(void)
{
    char word[MAX_WORD_LEN];
    int count;

    printf("Enter a word: ");
    if (scanf("%31s", word) != 1) {
        fprintf(stderr, "Error reading word.\n");
        return 1;
    }

    printf("Enter a count: ");
    if (scanf("%d", &count) != 1 || count < 0) {
        fprintf(stderr, "Invalid count.\n");
        return 1;
    }

    size_t word_len = strlen(word);
    size_t total_size = word_len * (size_t)count + 1;

    if (word_len > 0 && count > 0 && total_size - 1 < word_len) {
        fprintf(stderr, "Cannot allocate new string. Exiting...\n");
        return 1;
    }

    char *result = malloc(total_size);
    if (result == NULL) {
        fprintf(stderr, "Cannot allocate new string. Exiting...\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        strcpy(result + i * word_len, word);
    }

    printf("Your word is %s\n", result);

    free(result);
    return 0;
}

