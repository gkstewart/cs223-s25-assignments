//Gabby 4/22
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// signal handler for SIGINT
void handle_sigint(int sig) {
    printf("I've been shot\n");
    exit(0);
}

int main() {
    // signal handler
    signal(SIGINT, handle_sigint);

    while (1) {
        pause();  // Wait 
    }

    return 0;
}
