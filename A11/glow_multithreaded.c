#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

int clamp(int value, int min, int max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

struct thread_data {
  int id;
  int width, height;
  int start_row, end_row;
  int threshold, blur_size;
  struct ppm_pixel* original;
  struct ppm_pixel* bright;
  struct ppm_pixel* blurred;
  struct ppm_pixel* result;
};

void* glow_worker(void* arg) {
  struct thread_data* data = (struct thread_data*)arg;
  int width = data->width;
  int start = data->start_row;
  int end = data->end_row;
  int size = data->blur_size;
  int half = size / 2;

  printf("Thread sub-image slice: rows (%d,%d)\n", start, end);

  for (int y = start; y < end; y++) {
    for (int x = 0; x < width; x++) {
      int idx = y * width + x;
      int brightness = (data->original[idx].red + data->original[idx].green + data->original[idx].blue) / 3;
      if (brightness >= data->threshold) {
        data->bright[idx] = data->original[idx];
      } else {
        data->bright[idx].red = data->bright[idx].green = data->bright[idx].blue = 0;
      }
    }
  }

  for (int y = start; y < end; y++) {
    for (int x = 0; x < width; x++) {
      int red = 0, green = 0, blue = 0, count = 0;
      for (int dy = -half; dy <= half; dy++) {
        for (int dx = -half; dx <= half; dx++) {
          int ny = clamp(y + dy, 0, data->height - 1);
          int nx = clamp(x + dx, 0, width - 1);
          struct ppm_pixel p = data->bright[ny * width + nx];
          red += p.red;
          green += p.green;
          blue += p.blue;
          count++;
        }
      }
      int idx = y * width + x;
      data->blurred[idx].red = red / count;
      data->blurred[idx].green = green / count;
      data->blurred[idx].blue = blue / count;
    }
  }

  for (int y = start; y < end; y++) {
    for (int x = 0; x < width; x++) {
      int idx = y * width + x;
      data->result[idx].red = clamp(data->original[idx].red + data->blurred[idx].red, 0, 255);
      data->result[idx].green = clamp(data->original[idx].green + data->blurred[idx].green, 0, 255);
      data->result[idx].blue = clamp(data->original[idx].blue + data->blurred[idx].blue, 0, 255);
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  int N = 4;
  int threshold = 200;
  int blursize = 24;
  const char* filename = "earth-small.ppm";

  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1) {
    switch (opt) {
      case 'N': N = atoi(optarg); break;
      case 't': threshold = atoi(optarg); break;
      case 'b': blursize = atoi(optarg); break;
      case 'f': filename = optarg; break;
      case '?': printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]); return 1;
    }
  }

  clock_t start = clock();

  int width, height;
  struct ppm_pixel* original = read_ppm(filename, &width, &height);
  assert(original != NULL);

  struct ppm_pixel* bright = malloc(sizeof(struct ppm_pixel) * width * height);
  struct ppm_pixel* blurred = malloc(sizeof(struct ppm_pixel) * width * height);
  struct ppm_pixel* result = malloc(sizeof(struct ppm_pixel) * width * height);

  pthread_t* threads = malloc(sizeof(pthread_t) * N);
struct thread_data* thread_args = malloc(sizeof(struct thread_data) * N);

  int rows_per_thread = height / N;

  for (int i = 0; i < N; i++) {
    thread_args[i] = (struct thread_data){
      .id = i,
      .width = width,
      .height = height,
      .start_row = i * rows_per_thread,
      .end_row = (i + 1) * rows_per_thread,
      .threshold = threshold,
      .blur_size = blursize,
      .original = original,
      .bright = bright,
      .blurred = blurred,
      .result = result
    };
    pthread_create(&threads[i], NULL, glow_worker, &thread_args[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  write_ppm("glow.ppm", result, width, height);

  free(original);
  free(bright);
  free(blurred);
  free(result);
  free(threads);
  free(thread_args);

  clock_t end = clock();
  printf("Time: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}
