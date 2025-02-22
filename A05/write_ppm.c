/*----------------------------------------------
 * Author: gabby s 
 * Date: feb 2025
 * Description: implementation of write_ppm
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!

#include "write_ppm.h"

int write_ppm(const char* filename, int width, int height, struct ppm_pixel* pixels) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    fprintf(file, "P6\n%d %d\n255\n", width, height);

    size_t data_size = width * height * sizeof(struct ppm_pixel);
    if (fwrite(pixels, 1, data_size, file) != data_size) {
        fprintf(stderr, "Error writing PPM data\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}
void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}
