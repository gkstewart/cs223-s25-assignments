/*----------------------------------------------
 * Author: Gabrielle Stewart 
 * Date: February 2025
 * Description: A program that randomly places a Wampus within a NxM grid. Then, fills in the remaining cells with their distance from the Wampus
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_grid(char **grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows, cols;
    printf("Number of rows: ");
    scanf("%d", &rows);
    printf("Number of columns: ");
    scanf("%d", &cols);

    char **grid = malloc(rows * sizeof(char *));
    if (grid == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        grid[i] = malloc(cols * sizeof(char));
        if (grid[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }
    }

    srand(time(NULL));
    int w_row = rand() % rows;
    int w_col = rand() % cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == w_row && j == w_col) {
                grid[i][j] = 'W';
            } else {
                grid[i][j] = '0' + abs(i - w_row) + abs(j - w_col);
            }
        }
    }

    print_grid(grid, rows, cols);

    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
