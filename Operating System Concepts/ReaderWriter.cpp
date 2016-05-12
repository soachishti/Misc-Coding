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

const int SIZE = 100;
semaphore lock(1);
semaphore okToRead(0);
semaphore okToWrite(0);
int AR;
int AW;
int WR;
int WW;
string store;

struct arguments {
    void* arg1;
    void* arg2;
    void* arg3;
};

void* Reader(void* _arg) {
    arguments arg = *(arguments*)_arg;
    lock.Acquire();
    WR++;
    while (AW > 0 || WW > 0)
        okToRead.Wait();
    WR--;
    AR++;
    lock.Release();
    
    // Access DB
    cout << "[READER] " << store.substr((int)arg.arg1, (int)arg.arg2) << endl;
    
    lock.Acquire();
    AR--;
    if (AR == 0 && WW > 0)
        okToWrite.Wake();
    lock.Release();
}

void* Writer(void* _arg) {
    arguments arg = *(arguments*)_arg;
    lock.Acquire();
    WW++;
    if ((AW + AR) > 0)
        okToWrite.Sleep();
    WW--;
    AW++;
    lock.Release();
    
    // Access DB
    cout << "[WRITER] " << *((string*)arg.arg2) << endl;
    store.insert((int)arg.arg1, *((string*)arg.arg2));
        
    lock.Acquire();
    AW--;
    if (WW > 0)
        okToWrite.Wake();
    else
        okToRead.Broadcast(); // Wake All Readers
    lock.Release();
}


int main() {
    pthread_t thread[3];
    string str = "Syed Owais Ali Chishti";
    
    arguments arg_t1 = {0, &str};
    arguments arg_t2 = {(void*)0, (void*)5};
    pthread_create(&thread[0], NULL, Reader, &arg_t2);
    
    pthread_create(&thread[1], NULL, Writer, &arg_t1);
    
    sleep(1);
    pthread_create(&thread[2], NULL, Reader, &arg_t2);
    
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    pthread_join(thread[2], NULL);
}