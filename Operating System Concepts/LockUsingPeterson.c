// Name: Syed Owais Ali Chishti
// Task: Using Peterson Algorithm (turn + interested)

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define true 1 
#define false 0 
#define bool char 

int myGlobal = 0;
bool interested[2] = {false};
int turn = 0;
void lock(int own, int other) {
    turn = own;
    interested[own] = true;
    while(interested[other] == true && turn == own);
}

void unlock(int own, int other) {
    interested[own] = false; 
}

void *threadFunction(void * n) {
    int i, j;
    for (i = 0; i<5; i++) {
        lock(2, 1);
        
        j = myGlobal;
        j = j+1;
        printf(".");
        fflush(stdout);
        sleep(1);
        myGlobal = j;
        
        unlock(2, 1);
    }
}

int main() {
    pthread_t myThread;
    int i;
    pthread_create(&myThread, NULL,
                   threadFunction,
                   NULL);
    for (i = 0; i < 5; i++) {
        
        lock(1, 2);
        myGlobal = myGlobal + 1;
        unlock(1, 2);
        
        printf("o");
        fflush(stdout);
        sleep(1);
    }
    pthread_join(myThread, NULL);
    printf("\nMy Global Is: %d\n", myGlobal);
    exit(0);
}