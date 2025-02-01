/***************************************************
 * Author: Gabrielle Stewart
 * This program asks the user for a word and creates a bad password from it. 
 * January 2025
 */
#include <stdio.h>

void bad_password(char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == 'e') {
            word[i] = '3';
        } else if (word[i] == 'l') {
            word[i] = '1';
        } else if (word[i] == 'a') {
            word[i] = '@';
        }
    }
}

int main() {
    char word[100]; // Assuming the input won't exceed 99 characters

    printf("Enter a word: ");
    scanf("%99s", word);

    bad_password(word);

    printf("Your bad password is %s\n", word);

    return 0;
}
