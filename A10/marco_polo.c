// Gabrielle Stewart
// April 1st
// This program uses signals to coordinate between two processes.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

pid_t child_pid = 0;
pid_t parent_pid = 0;

void parent_handler(int sig) {
    if (sig == SIGALRM) {
        printf("polo [%d]\n", getpid());
        fflush(stdout);
    }
}

void child_handler(int sig) {
    if (sig == SIGALRM) {
        printf("marco [%d]\n", getpid());
        fflush(stdout);
        kill(parent_pid, SIGALRM);
    }
}

int main() {
    parent_pid = getpid();
    child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Child 
        signal(SIGALRM, child_handler);

        // wait
        while (1) {
            pause();
        }

    } else {
        // Parent 
        signal(SIGALRM, parent_handler);

        printf("Parent is %d\n", parent_pid);
        fflush(stdout);

        char cmd;
        while (1) {
            cmd = getchar();
            if (cmd == 'm') {
                kill(child_pid, SIGALRM);
            } else if (cmd == 'q') {
                kill(child_pid, SIGTERM);
                break;
            }
        }

        // Wait
        wait(NULL);
    }

    return 0;
}
