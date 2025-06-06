#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

struct account {
  float balance;
  pthread_mutex_t lock;
  pthread_cond_t cond;
};

struct thread_data {
  struct account* fromAccount;
  struct account* toAccount;
  float amount;
};

void lock_accounts(struct account* acct1, struct account* acct2) {
  if (acct1 < acct2) {
    pthread_mutex_lock(&acct1->lock);
    pthread_mutex_lock(&acct2->lock);
  } else {
    pthread_mutex_lock(&acct2->lock);
    pthread_mutex_lock(&acct1->lock);
  }
}

void unlock_accounts(struct account* acct1, struct account* acct2) {
  pthread_mutex_unlock(&acct1->lock);
  pthread_mutex_unlock(&acct2->lock);
}

void *Transfer(void *args) {
  struct thread_data* data = (struct thread_data*) args;
  struct account* fromAcct = data->fromAccount;
  struct account* toAcct = data->toAccount;
  float amt = data->amount;

  for (int i = 0; i < 1000; i++) {
    // lock both accounts
    lock_accounts(fromAcct, toAcct);

    // wait 
    while (fromAcct->balance < amt) {
      pthread_cond_wait(&fromAcct->cond, &fromAcct->lock);
    }

    fromAcct->balance -= amt;
    assert(fromAcct->balance >= 0);
    toAcct->balance += amt;

    pthread_cond_signal(&toAcct->cond);

    unlock_accounts(fromAcct, toAcct);
  }

  return NULL;
}

int main() {
  struct account A, B;
  A.balance = 5000;
  B.balance = 5000;
  pthread_mutex_init(&A.lock, NULL);
  pthread_mutex_init(&B.lock, NULL);
  pthread_cond_init(&A.cond, NULL);
  pthread_cond_init(&B.cond, NULL);

  printf("Starting balance A: %.2f\n", A.balance);
  printf("Starting balance B: %.2f\n", B.balance);

  struct thread_data dataA = { .fromAccount = &B, .toAccount = &A, .amount = 1000 };
  struct thread_data dataB = { .fromAccount = &A, .toAccount = &B, .amount = 1000 };

  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, Transfer, &dataA);
  pthread_create(&thread2, NULL, Transfer, &dataB);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Ending balance A: %.2f\n", A.balance);
  printf("Ending balance B: %.2f\n", B.balance);

  pthread_mutex_destroy(&A.lock);
  pthread_mutex_destroy(&B.lock);
  pthread_cond_destroy(&A.cond);
  pthread_cond_destroy(&B.cond);

  return 0;
}