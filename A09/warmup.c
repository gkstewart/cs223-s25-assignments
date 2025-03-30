#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("[%d] A0\n", getpid());

    pid_t pidB = fork();
    if (pidB == 0) {  
        printf("[%d] B0\n", getpid());

        pid_t pidB1 = fork();
        if (pidB1 == 0) {  
            printf("[%d] B1\n", getpid());
            printf("[%d] Bye\n", getpid());
            exit(0);
        }

        wait(NULL);  
        printf("[%d] Bye\n", getpid());
        exit(0);
    }

    wait(NULL);  // wait B finishes before proceeding to C

    pid_t pidC = fork();
    if (pidC == 0) {  
        printf("[%d] C0\n", getpid());

        pid_t pidC1 = fork();
        if (pidC1 == 0) { 
            printf("[%d] C1\n", getpid());
            printf("[%d] Bye\n", getpid());
            exit(0);
        }

        wait(NULL); 
        printf("[%d] Bye\n", getpid());
        exit(0);
    }

    wait(NULL);  
    return 0;
}