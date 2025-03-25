#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("[%d] A0\n", getpid());

    pid_t pidB = fork();
    if (pidB == 0) {  // Child B
        printf("[%d] B0\n", getpid());

        pid_t pidB1 = fork();
        if (pidB1 == 0) {  // Child B1
            printf("[%d] B1\n", getpid());
            printf("[%d] Bye\n", getpid());
            exit(0);
        }

        wait(NULL);  // Wait for B1
        printf("[%d] Bye\n", getpid());
        exit(0);
    }

    pid_t pidC = fork();
    if (pidC == 0) {  // Child C
        printf("[%d] C0\n", getpid());

        pid_t pidC1 = fork();
        if (pidC1 == 0) {  // Child C1
            printf("[%d] C1\n", getpid());
            printf("[%d] Bye\n", getpid());
            exit(0);
        }

        wait(NULL);  // Wait for C1
        printf("[%d] Bye\n", getpid());
        exit(0);
    }

    wait(NULL);  // Wait for B
    wait(NULL);  // Wait for C
    return 0;
}