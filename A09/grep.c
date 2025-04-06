#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

void search_file(const char *filename, const char *keyword) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Process [%d] Error: Cannot open file %s\n", getpid(), filename);
        exit(0);
    }

    char line[1024];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, keyword)) {
            count++;
            printf("Process [%d] Found in %s: %s", getpid(), filename, line);
        }
    }

    fclose(file);
    exit(count);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("usage: ./grep <NumProcesses> <Keyword> <Files>\n");
        return 1;
    }

    int num_processes = atoi(argv[1]);
    const char *keyword = argv[2];
    int num_files = argc - 3;
    char **files = &argv[3];

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int per_process = num_files / num_processes;
    int remaining = num_files % num_processes;
    int index = 0, total_count = 0;

    for (int i = 0; i < num_processes; i++) {
        int num_assigned = per_process + (i < remaining ? 1 : 0);
        if (num_assigned == 0) break;

        pid_t pid = fork();
        if (pid == 0) { 
            for (int j = 0; j < num_assigned; j++) {
                search_file(files[index++], keyword);
            }
            exit(0);
        }
    }

    for (int i = 0; i < num_processes; i++) {
        int status;
        wait(&status);
        total_count += WEXITSTATUS(status);
    }

    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("Total occurrences: %d\n", total_count);
    printf("Elapsed time: %.6f seconds\n", elapsed);

    return 0;
}