/***************************************************
 * Author: Gabrielle Stewart
 * This program  maintains a list of snacks available for purchase. 
 * January 2025
 */
#include <stdio.h>

struct snack {
    char name[20];
    double cost;
    int quantity;
};

int main() {
    struct snack snacks[] = {
        {"Cheese crackers", 1.50, 4},
        {"Applesauce", 15.50, 6},
        {"Ramen", 0.50, 0}
    };

    int num_snacks = sizeof(snacks) / sizeof(snacks[0]);
    double money;

    printf("Welcome to Steven Struct's Snack Bar.\n\n");

    printf("How much money do you have? ");
    scanf("%lf", &money);

    for (int i = 0; i < num_snacks; i++) {
        printf("%d) %-20s cost: $%.2f quantity: %d\n", i, snacks[i].name, snacks[i].cost, snacks[i].quantity);
    }

    int choice;
    printf("\nWhat snack would you like to buy? [0,1,2] ");
    scanf("%d", &choice);

    if (choice < 0 || choice >= num_snacks) {
        printf("Invalid choice!\n");
        return 1;
    }

    if (snacks[choice].quantity == 0) {
        printf("Sorry, we are out of %s\n", snacks[choice].name);
    } else if (money < snacks[choice].cost) {
        printf("You can't afford it!\n");
    } else {
        money -= snacks[choice].cost;
        snacks[choice].quantity--;
        printf("You bought %s\n", snacks[choice].name);
        printf("You have $%.2f left\n", money);
    }

    return 0;
}
