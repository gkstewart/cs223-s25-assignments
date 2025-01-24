/***************************************************
 * mathgame.c
 * Author: Gabrielle Stewart 
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    printf("Welcome to Math Game!\n");
    printf("How many rounds do you want to play? ");

    int rounds;
    scanf("%d", &rounds);

    int correct_answers = 0;

    for (int i = 0; i < rounds; i++) {
        int num1 = rand() % 9 + 1;
        int num2 = rand() % 9 + 1;

        printf("%d + %d = ? ", num1, num2);

        int answer;
        scanf("%d", &answer);

        if (answer == num1 + num2) {
            printf("Correct!\n");
            correct_answers++;
        } else {
            printf("Incorrect :(\n");
        }
    }

    printf("You answered %d/%d correctly.\n", correct_answers, rounds);

    return 0;
}
