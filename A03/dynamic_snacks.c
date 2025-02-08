/*----------------------------------------------
 * Author: Gabrielle Stewart 
 * Date: February 2025
 * Description: update to last weeks snackbar program that allows user to add snacks.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

struct snack {
    char name[20];
    double cost;
    int quantity;
};

int main() {
    int num_snacks;
    
    printf("Enter a number of snacks: ");
    if (scanf("%d", &num_snacks) != 1 || num_snacks <= 0) {
        fprintf(stderr, "Invalid number of snacks.\n");
        return 1;
    }
    
    struct snack *snacks = malloc(num_snacks * sizeof(struct snack));
    if (snacks == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    
    for (int i = 0; i < num_snacks; i++) {
        printf("Enter a name: ");
        scanf("%19s", snacks[i].name);
        
        printf("Enter a price: ");
        if (scanf("%lf", &snacks[i].cost) != 1) {
            fprintf(stderr, "Invalid cost.\n");
            free(snacks);
            return 1;
        }
        
        printf("Enter a quantity: ");
        if (scanf("%d", &snacks[i].quantity) != 1) {
            fprintf(stderr, "Invalid quantity.\n");
            free(snacks);
            return 1;
        }
    }
    
    printf("\nWelcome to My Snack Bar.\n\n");
    for (int i = 0; i < num_snacks; i++) {
        printf("%d) %-20s cost: $%.2f quantity: %d\n", i, snacks[i].name, snacks[i].cost, snacks[i].quantity);
    }
    
    free(snacks);
    return 0;
}

