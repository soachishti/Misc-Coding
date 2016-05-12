// Name: Syed Owais Ali Chishti
// Task: Using turn variable implement synchronization

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int myGlobal = 0;
int turn = 1;

void lock(int lock) {
    while(turn != lock);
}

void unlock(int lock) {
    turn = lock;
}

void *threadFunction(void * n) {
    int i, j;
    for (i = 0; i<5; i++) {
        lock(2);
        
        j = myGlobal;
        j = j+1;
        printf(".");
        fflush(stdout);
        sleep(1);
        myGlobal = j;
        
        unlock(1);
    }
}

int main() {
    pthread_t myThread;
    int i;
    pthread_create(&myThread, NULL,
                   threadFunction,
                   NULL);
    for (i = 0; i < 5; i++) {
        
        lock(1);
        myGlobal = myGlobal + 1;
        unlock(2);
        
        printf("o");
        fflush(stdout);
        sleep(1);
    }
    pthread_join(myThread, NULL);
    printf("\nMy Global Is: %d\n", myGlobal);
    exit(0);
}