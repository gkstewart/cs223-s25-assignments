/*----------------------------------------------
 * Author:Gabby Stewart 
 * Date: February 12,2025
 * Description: a program that allows users to add snacks to the snackbar and displays them in alphabetical order. 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Snack {
    char name[50];
    float cost;
    int quantity;
    struct Snack *next;
} Snack;

Snack *insert_first(Snack *head, char *name, float cost, int quantity) {
    Snack *new_snack = (Snack *)malloc(sizeof(Snack));
    if (!new_snack) {
        printf("Memory allocation failed!\n");
        return head;
    }
    strcpy(new_snack->name, name);
    new_snack->cost = cost;
    new_snack->quantity = quantity;
    new_snack->next = head;
    return new_snack;
}

void clear(Snack *head) {
    Snack *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printList(Snack *head) {
    int index = 0;
    printf("\nWelcome to Sorted Linked List Snack Bar.\n\n");
    Snack *current = head;
    while (current) {
        printf("%d) %-20s cost: $%.2f     quantity: %d\n", index++, current->name, current->cost, current->quantity);
        current = current->next;
    }
}

Snack *sortName(Snack *head) {
    if (!head || !head->next) return head;
    Snack *sorted = NULL;
    Snack *current = head;
    while (current) {
        Snack *next = current->next;
        if (!sorted || strcmp(current->name, sorted->name) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            Snack *temp = sorted;
            while (temp->next && strcmp(current->name, temp->next->name) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    return sorted;
}

int main() {
    int num_snacks;
    printf("Enter a number of snacks: ");
    scanf("%d", &num_snacks);

    Snack *snack_list = NULL;
    for (int i = 0; i < num_snacks; i++) {
        char name[50];
        float cost;
        int quantity;

        printf("Enter a name: ");
        scanf("%s", name);
        printf("Enter a cost: ");
        scanf("%f", &cost);
        printf("Enter a quantity: ");
        scanf("%d", &quantity);

        snack_list = insert_first(snack_list, name, cost, quantity);
    }

    snack_list = sortName(snack_list);
    printList(snack_list);
    clear(snack_list);

    return 0;
}

