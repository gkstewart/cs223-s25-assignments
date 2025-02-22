/*----------------------------------------------
 * Author: Gabby S. 
 * Date: Feb 2025
 * Description: implementation of read_ppm in read_ppm.c
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"
#include <time.h>
// Choose *one* to implement (do not remove the other one!)

struct ppm_pixel* read_ppm(const char* filename, int* width, int* height) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    char format[3];
    if (!fgets(format, sizeof(format), file) || format[0] != 'P' || format[1] != '6') {
        fprintf(stderr, "Invalid PPM format\n");
        fclose(file);
        return NULL;
    }

    char comment[256];
    if (fgets(comment, sizeof(comment), file) == NULL) {
        fprintf(stderr, "Error reading comment line\n");
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d %d", width, height) != 2) {
        fprintf(stderr, "Error reading image dimensions\n");
        fclose(file);
        return NULL;
    }

    int maxval;
    if (fscanf(file, "%d", &maxval) != 1 || maxval != 255) {
        fprintf(stderr, "Invalid max value in PPM file\n");
        fclose(file);
        return NULL;
    }
    fgetc(file);

    size_t data_size = (*width) * (*height);
    struct ppm_pixel* pixels = (struct ppm_pixel*)malloc(data_size * sizeof(struct ppm_pixel));
    if (!pixels) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    if (fread(pixels, sizeof(struct ppm_pixel), data_size, file) != data_size) {
        fprintf(stderr, "Error reading PPM data\n");
        free(pixels);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return pixels;
}

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
    
    srand(time(NULL));
    for (int i = 0; i < width * height; i++) {
        pixels[i].red <<= (rand() % 2);
        pixels[i].green <<= (rand() % 2);
        pixels[i].blue <<= (rand() % 2);
    }
    
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

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}
