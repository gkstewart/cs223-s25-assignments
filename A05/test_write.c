/*----------------------------------------------
 * Author: gabby s 
 * Date: feb 2025
 * Description test for write
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"
int main() {
    int width, height;
    struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &width, &height);
    
    if (!pixels) {
        fprintf(stderr, "Failed to read PPM file.\n");
        return 1;
    }

    if (!write_ppm("test.ppm", width, height, pixels)) {
        fprintf(stderr, "Failed to write PPM file.\n");
        free(pixels);
        return 1;
    }

    free(pixels);

    pixels = read_ppm("test.ppm", &width, &height);
    if (!pixels) {
        fprintf(stderr, "Failed to read test PPM file.\n");
        return 1;
    }

    printf("Testing file test.ppm: %d %d\n", width, height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            struct ppm_pixel p = pixels[i * width + j];
            printf("(%d,%d,%d) ", p.red, p.green, p.blue);
        }
        printf("\n");
    }

    free(pixels);
    return 0;
}
