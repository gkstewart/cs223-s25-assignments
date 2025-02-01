/***************************************************
 * Author: Gabrielle Stewart
 * This program  asks the user for a word and then encodes it using a shift cypher.
 */
#include <stdio.h>

void shift_cypher(char *word, int shift) {
    for (int i = 0; word[i] != '\0'; i++) {
        char ch = word[i];
        char new_ch = ((ch - 'a' + shift) % 26 + 26) % 26 + 'a';
        word[i] = new_ch;
    }
}

int main() {
    char word[100];
    int shift;

    printf("Enter a word: ");
    scanf("%99s", word);

    printf("Enter a shift: ");
    scanf("%d", &shift);

    shift_cypher(word, shift);

    printf("Your cypher is %s\n", word);

    return 0;
}
