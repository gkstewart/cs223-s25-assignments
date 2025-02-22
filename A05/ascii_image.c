/*----------------------------------------------
 * Author: Gabby s 
 * Date: feb 2025
 * Description: This program reads a binary PPM file, converts its pixel intensities to ASCII characters, and prints the resulting ASCII image to the console
 ---------------------------------------------*/
#include <stdio.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

char get_ascii_char(int intensity) {
    if (intensity <= 25) return '@';
    if (intensity <= 50) return '#';
    if (intensity <= 75) return '%';
    if (intensity <= 100) return '*';
    if (intensity <= 125) return 'o';
    if (intensity <= 150) return ';';
    if (intensity <= 175) return ':';
    if (intensity <= 200) return ',';
    if (intensity <= 225) return '.';
    return ' ';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ppm file>\n", argv[0]);
        return 1;
    }

    int width, height;
    struct ppm_pixel *pixels = read_ppm(argv[1], &width, &height);
    if (!pixels) {
        fprintf(stderr, "Failed to read PPM file.\n");
        return 1;
    }

    printf("Reading %s with width %d and height %d\n", argv[1], width, height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            struct ppm_pixel p = pixels[i * width + j];
            int intensity = (p.red + p.green + p.blue) / 3;
            printf("%c", get_ascii_char(intensity));
        }
        printf("\n");
    }

    free(pixels);
    return 0;
}
