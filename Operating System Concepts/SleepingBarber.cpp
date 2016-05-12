/*
Name: Syed Owais Ali Chisht
Roll no: p146011
Section: A
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <math.h>
using namespace std;

class semaphore {
    sem_t S;
public:
    semaphore(int n = 1) {
        if (sem_init(&S,0,n) == -1)
            throw "Failed to initialize semaphore";
    }
    
    void V() { // Wake/Signal
        sem_post(&S);
    }
    
    void P() { // Sleep/Wait
        sem_wait(&S);
    }
    
    bool isZero() {
        int tmp;
        sem_getvalue(&S, &tmp);
        return (tmp == 0);
    }
};

semaphore FreeBarber(0);
semaphore Customer(5);

void getHairCut() {
    FreeBarber.V(); // Wakeup barber
    cout << "[getHairCut] Customer want hair cut" << endl;
    fflush(stdout);
}

void cutHair() {
    cout << "[BARBER] Cutting hair" << endl;
    fflush(stdout);
}

void balk() {
    cout << "[CUSTOMER] Left because shop full" << endl;
    fflush(stdout);
    pthread_exit(NULL);
}

void* barber(void *) {
    while(1) {
        if (FreeBarber.isZero()) {
            cout << "[BARBER] Sleeping" << endl;
            fflush(stdout);
        }
        FreeBarber.P(); // Sleep barber, Will be wakeup by customer
        cutHair();
        sleep(1); // Added so that customer are not service real time.
        Customer.V(); // Customer left shop
    }
}

void* customer(void *) {
    cout << "[CUSTOMER] Arrived" << endl;
    fflush(stdout);
    if (Customer.isZero()) // Shop full, leave. 
        balk();
    Customer.P();   // Customer arrived, Sleep if chair are full 
    getHairCut();
}

int main() {
    cout << "STARTED" << endl;
    const int TOTAL_CHAIR = 7+1; // 5 for customer, 1 for barber
    pthread_t thread[TOTAL_CHAIR];
    pthread_create(&thread[0], NULL, barber, NULL);
    
    for (int i = 1; i <= TOTAL_CHAIR; i++) {
        pthread_create(&thread[i], NULL, customer, NULL);
        usleep(1000);
    }
    
    for (int i = 0; i < TOTAL_CHAIR; i++)
        pthread_join(thread[i], NULL);
}