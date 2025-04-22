//Gabby 4/22
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check for command line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open file
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    int c = fgetc(fp);
    while (c != EOF) {
        // Shift character to right to decode
        c = (c >> 1) & 0x7F;  // right shift
        printf("%c", c);
        c = fgetc(fp);
    }

    fclose(fp);
    return 0;
}
