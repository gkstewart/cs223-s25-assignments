// Gabrielle Stewart
//April 1st
// This program uses N threads to search for a keyword in a set of files.
#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

typedef struct { //struct
    int thread_id;
    int start_index;
    int end_index;
    char **files;
    char *keyword;
    int match_count;
} ThreadArgs;

void* grep_thread(void* args) {
    ThreadArgs* targs = (ThreadArgs*) args;
    int matches = 0;

    for (int i = targs->start_index; i < targs->end_index; i++) {
        FILE *fp = fopen(targs->files[i], "r");
        if (!fp) {
            fprintf(stderr, "Thread %d: Failed to open the file! %s\n", targs->thread_id, targs->files[i]);
            continue;
        }

        char line[MAX_LINE_LEN];
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, targs->keyword)) {
                printf("[Thread %d] %s: %s", targs->thread_id, targs->files[i], line);
                matches++;
            }
        }

        fclose(fp);
    }

    targs->match_count = matches;
    pthread_exit(NULL);
}
int main(int argc, char* argv[]) { //main
  if (argc < 4) {
      fprintf(stderr, "usage: ./grep <NumThreads> <Keyword> <Files>\n");
      return 1;
  }

  int num_threads = atoi(argv[1]);
  char *keyword = argv[2];
  int num_files = argc - 3;
  char **file_list = &argv[3];

  if (num_threads <= 0 || num_files == 0) {
      fprintf(stderr, "Invalid number of threads or files.\n");
      return 1;
  }

  if (num_threads > num_files) {
      num_threads = num_files;
  }

  pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
  ThreadArgs *thread_args = malloc(sizeof(ThreadArgs) * num_threads);

  int files_per_thread = num_files / num_threads;
  int remainder = num_files % num_threads;
  int file_index = 0;

  for (int i = 0; i < num_threads; i++) {
      thread_args[i].thread_id = i;
      thread_args[i].keyword = keyword;
      thread_args[i].files = file_list;
      thread_args[i].start_index = file_index;
      thread_args[i].end_index = file_index + files_per_thread + (i < remainder ? 1 : 0);
      thread_args[i].match_count = 0;

      pthread_create(&threads[i], NULL, grep_thread, &thread_args[i]);
      file_index = thread_args[i].end_index;
  }

  int total_matches = 0;
  for (int i = 0; i < num_threads; i++) {
      pthread_join(threads[i], NULL);
      total_matches += thread_args[i].match_count;
  }

  printf("Total matches: %d\n", total_matches);

  free(threads); //free
  free(thread_args); //free

  return 0;
}
