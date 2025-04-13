#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read_ppm.h"

// skip comments and whitespace
void skip_comments(FILE* fp) {
  int ch;
  while ((ch = fgetc(fp)) != EOF) {
    if (isspace(ch)) {
      continue;
    } else if (ch == '#') {
      while ((ch = fgetc(fp)) != '\n' && ch != EOF); // skip rest of line
    } else {
      ungetc(ch, fp);
      break;
    }
  }
}

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE* fp = fopen(filename, "rb");
  if (!fp) {
    perror("Error opening file");
    return NULL;
  }

  char format[3];
  if (fscanf(fp, "%2s", format) != 1 || strcmp(format, "P6") != 0) {
    fprintf(stderr, "Invalid header format\n");
    fclose(fp);
    return NULL;
  }

  skip_comments(fp);
  if (fscanf(fp, "%d", w) != 1) {
    fprintf(stderr, "Invalid width\n");
    fclose(fp);
    return NULL;
  }

  skip_comments(fp);
  if (fscanf(fp, "%d", h) != 1) {
    fprintf(stderr, "Invalid height\n");
    fclose(fp);
    return NULL;
  }

  int maxval;
  skip_comments(fp);
  if (fscanf(fp, "%d", &maxval) != 1 || maxval != 255) {
    fprintf(stderr, "Invalid maxval (must be 255)\n");
    fclose(fp);
    return NULL;
  }

  fgetc(fp); 

  int total_pixels = (*w) * (*h);
  struct ppm_pixel* pixels = malloc(sizeof(struct ppm_pixel) * total_pixels);
  if (!pixels) {
    perror("Memory allocation failed");
    fclose(fp);
    return NULL;
  }

  if (fread(pixels, sizeof(struct ppm_pixel), total_pixels, fp) != total_pixels) {
    fprintf(stderr, "Error reading pixel data\n");
    free(pixels);
    fclose(fp);
    return NULL;
  }

  fclose(fp);
  return pixels;
}