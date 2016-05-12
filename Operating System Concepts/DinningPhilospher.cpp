/*
Name: Syed Owais Ali Chishti
Roll no: p146011
Section: A
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
using namespace std;

class semaphore {
    sem_t S;
    int n;
  public:
    semaphore(int t = 1) {
        n = t;
        if (sem_init(&S,0,n) == -1)
            throw "Failed to initialize semaphore";
    }

    void V() { // Wake/Signal
        sem_post(&S);
    }

    void P() { // Sleep/Wait
        sem_wait(&S);
    }

    void Signal() {
        V();
    }
    void Wait() {
        P();
    }

    void Wake() {
        V();
    }
    void Sleep() {
        P();
    }

    void Release() {
        V();
    }
    void Acquire() {
        P();
    }

    void Broadcast() {
        while (getValue() == n) {
            Wake();
        }
    }

    int getValue() {
        int tmp;
        sem_getvalue(&S, &tmp);
        return tmp;
    }

    bool isZero() {
        return (getValue() == 0);
    }
};

const int N = 5;
semaphore lock(1);
semaphore CV[N] = {0};
enum Status {THINKING, HUNGRY, EATING};
Status status[N];

int Left(int i) {
    return (i + N - 1) % N;
}

int Right(int i) {
    return (i + N) % N;
}

void Eat(int i) {
    cout << "[EATING] Philospher " << i << endl;
    fflush(stdout);
}

void*  Philospher(void* _i) {
    int i = (int)_i;
    lock.Acquire();
    cout << "[ONTABLE] Philospher " << i << "\n";
    status[i] = HUNGRY;
    cout << "[HUNGRY] Philospher " << i << endl;
    while(status[Left(i)] == EATING || status[Left(i)] == EATING) {
        lock.Release();
        CV[i].Wait();
        lock.Acquire();
    }
    status[i] = EATING;
    lock.Release();
    Eat(i);
    lock.Acquire();
    status[i] = THINKING;
    cout << "[THINKING] Philospher " << i << endl;
    CV[Left(i)].Signal();
    CV[Right(i)].Signal();
    lock.Release();
}

int main() {
    cout << "TABLE INITIATED\n";
    pthread_t thread[5];
    
    for (int i = 0; i < 5; i++) {
        pthread_create(&thread[i], NULL, Philospher, (void*)i);
    }
    
    for (int i = 0; i < 5; i++)        
        pthread_join(thread[i], NULL); 
}