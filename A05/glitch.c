/*----------------------------------------------
 * Author:gabby s 
 * Date: feb 2025
 * Description: This program reads a PPM file, applies a glitch effect by shifting pixel values randomly, and saves the modified image
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "read_ppm.h"
#include "write_ppm.h"

void apply_glitch(struct ppm_pixel *pixels, int width, int height) {
    srand(time(NULL));
    for (int i = 0; i < width * height; i++) {
        pixels[i].red <<= (rand() % 2);
        pixels[i].green <<= (rand() % 2);
        pixels[i].blue <<= (rand() % 2);
    }
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

    apply_glitch(pixels, width, height);

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s-glitch.ppm", argv[1]);
    printf("Writing file %s\n", output_filename);

    if (!write_ppm(output_filename, width, height, pixels)) {
        fprintf(stderr, "Failed to write glitch PPM file.\n");
        free(pixels);
        return 1;
    }

    free(pixels);
    return 0;
}
