#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define N 10

int buffer[N];
int in = 0;
int out = 0;
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

int produce_item() {
    return rand() % 10;
}

void consume_item(int item) {
    printf("Received item: %d\n", item);
    fflush(stdout);
}

void* producer(void* arg) {
    while (1) {
        sleep(1);
        int item = produce_item();

        pthread_mutex_lock(&mutex);
        while (count == N)
            pthread_cond_wait(&not_full, &mutex);

        buffer[in] = item;
        in = (in + 1) % N;
        count++;

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (count == 0)
            pthread_cond_wait(&not_empty, &mutex);

        int item = buffer[out];
        out = (out + 1) % N;
        count--;

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);

        consume_item(item);
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    srand(time(NULL));

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    return 0;
}

