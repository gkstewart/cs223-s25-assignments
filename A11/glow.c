#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

#define THRESHOLD 200
#define BLUR_BOX_SIZE 25

int clamp(int value, int min, int max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

struct ppm_pixel* extract_bright(struct ppm_pixel* original, int width, int height) {
  int size = width * height;
  struct ppm_pixel* bright = malloc(sizeof(struct ppm_pixel) * size);
  for (int i = 0; i < size; i++) {
    int brightness = (original[i].red + original[i].green + original[i].blue) / 3;
    if (brightness >= THRESHOLD) {
      bright[i] = original[i];
    } else {
      bright[i].red = bright[i].green = bright[i].blue = 0;
    }
  }
  return bright;
}

struct ppm_pixel* blur_image(struct ppm_pixel* input, int width, int height) {
  struct ppm_pixel* blurred = malloc(sizeof(struct ppm_pixel) * width * height);
  int half = BLUR_BOX_SIZE / 2;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int red = 0, green = 0, blue = 0;
      int count = 0;

      for (int dy = -half; dy <= half; dy++) {
        for (int dx = -half; dx <= half; dx++) {
          int nx = clamp(x + dx, 0, width - 1);
          int ny = clamp(y + dy, 0, height - 1);
          struct ppm_pixel p = input[ny * width + nx];
          red += p.red;
          green += p.green;
          blue += p.blue;
          count++;
        }
      }

      int idx = y * width + x;
      blurred[idx].red = red / count;
      blurred[idx].green = green / count;
      blurred[idx].blue = blue / count;
    }
  }

  return blurred;
}

struct ppm_pixel* add_images(struct ppm_pixel* a, struct ppm_pixel* b, int width, int height) {
  int size = width * height;
  struct ppm_pixel* result = malloc(sizeof(struct ppm_pixel) * size);
  for (int i = 0; i < size; i++) {
    result[i].red = clamp(a[i].red + b[i].red, 0, 255);
    result[i].green = clamp(a[i].green + b[i].green, 0, 255);
    result[i].blue = clamp(a[i].blue + b[i].blue, 0, 255);
  }
  return result;
}

int main(int argc, char* argv[]) {
  clock_t start = clock();

  int width, height;
  struct ppm_pixel* original = read_ppm("earth-small.ppm", &width, &height);
  assert(original != NULL);

  struct ppm_pixel* bright = extract_bright(original, width, height);
  struct ppm_pixel* blurred = blur_image(bright, width, height);
  struct ppm_pixel* final = add_images(original, blurred, width, height);

  write_ppm("glow.ppm", final, width, height);

  free(original);
  free(bright);
  free(blurred);
  free(final);

  clock_t end = clock();
  printf("Time: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
  return 0;
}