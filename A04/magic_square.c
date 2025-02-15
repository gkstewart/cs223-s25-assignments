/*----------------------------------------------
 * Author: Gabrielle Stewart 
 * Date: Febuary 12th, 2025
 * Description: A program that tests whether a given matrix is a magic square. 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

int is_magic_square(int **matrix, int n, int magic_constant) {
    int sum;

    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = 0; j < n; j++) {
            sum += matrix[i][j];
        }
        if (sum != magic_constant) return 0;
    }

    for (int j = 0; j < n; j++) {
        sum = 0;
        for (int i = 0; i < n; i++) {
            sum += matrix[i][j];
        }
        if (sum != magic_constant) return 0;
    }

    sum = 0;
    for (int i = 0; i < n; i++) {
        sum += matrix[i][i];
    }
    if (sum != magic_constant) return 0;

    sum = 0;
    for (int i = 0; i < n; i++) {
        sum += matrix[i][n - 1 - i];
    }
    if (sum != magic_constant) return 0;

    return 1;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2 || n != m) {
        printf("Invalid input. Matrix must be square.\n");
        return 1;
    }

    // malloc
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Invalid input.\n");
                return 1;
            }
        }
    }

    int magic_constant = 0;
    for (int j = 0; j < n; j++) {
        magic_constant += matrix[0][j];
    }

    if (is_magic_square(matrix, n, magic_constant)) {
        printf("M is a magic square (magic constant = %d)\n", magic_constant);
    } else {
        printf("M is NOT a magic square!\n");
    }

    // free  memory
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

