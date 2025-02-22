//Author: Gabrille Stewart
//date: Feb 2025
//read and write binary PPM files. 
#ifndef LOAD_PPM_H
#define LOAD_PPM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width, height;
    unsigned char *data; 
} PPMImage;

PPMImage *read_ppm(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }
    
    char format[3];
    if (fscanf(file, "%2s", format) != 1 || format[0] != 'P' || format[1] != '6') {
        fprintf(stderr, "Invalid PPM format\n");
        fclose(file);
        return NULL;
    }
    
    int width, height, maxval;
    if (fscanf(file, "%d %d %d", &width, &height, &maxval) != 3 || maxval != 255) {
        fprintf(stderr, "Invalid PPM header\n");
        fclose(file);
        return NULL;
    }
    fgetc(file);
    
    size_t data_size = width * height * 3;
    unsigned char *data = (unsigned char *)malloc(data_size);
    if (!data) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    if (fread(data, 1, data_size, file) != data_size) {
        fprintf(stderr, "Error reading PPM data\n");
        free(data);
        fclose(file);
        return NULL;
    }
    fclose(file);
    
    PPMImage *image = (PPMImage *)malloc(sizeof(PPMImage));
    image->width = width;
    image->height = height;
    image->data = data;
    return image;
}

int write_ppm(const char *filename, const PPMImage *image) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file");
        return 0;
    }
    
    fprintf(file, "P6\n%d %d\n255\n", image->width, image->height);
    size_t data_size = image->width * image->height * 3;
    if (fwrite(image->data, 1, data_size, file) != data_size) {
        fprintf(stderr, "Error writing PPM data\n");
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}
