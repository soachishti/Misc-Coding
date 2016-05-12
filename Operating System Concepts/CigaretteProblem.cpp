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
#include <math.h>
using namespace std;

enum Ingredient {TOBACCO, PAPER, MATCH}; 
pthread_t thread[3];
Ingredient table[2];
int Cigarette;

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

semaphore smoker[3] = {0, 0, 0};
semaphore arbiter(0);
semaphore lock(1); // Lock
semaphore print(1); // Lock

struct param {
    int id;
    int smoker;
};

void* Smoker(void* _id) {
    int id = (int)_id;
    Ingredient Own = (Ingredient)id; // Own the ingredient, Set by their IDs
    while(1) {
        if (smoker[id].isZero()) {
            print.P();
            cout << "[SMOKER " << id << "] Sleeping" << endl;
            print.V();
        }
        smoker[id].P(); // Sleep the smoker
        cout << "[SMOKER " << id << "] Woke" << endl;

        Cigarette = Own + table[0] + table[1]; // make cigarette from table ingredient
        
        //print.P();
        cout << "[SMOKER " << id << "] Smoked Cigarette" << endl;
        //print.V();
        sleep(1);
        arbiter.V(); // Wake Arbiter
        
    }
}

void* Arbiter(void*) {
    int i = 3; // No of Arbiter iteration
    while(i--) {
        int s1 = 0; // Smoker 1
        int s2 = 0; // Smoker 2
        int s3 = rand()%3;
        if (s3 == 0) { s1 = 1; s2 = 2;}
        else if (s3 == 1) { s1 = 0; s2 = 2;}
        else if (s3 == 2) { s1 = 0; s2 = 1;}
        
        //cout << s1 << " - " << s2 << " - " << s3 << endl;

        lock.P();
        // Put ingredient on table
        table[s1] = (Ingredient) s1;
        print.P();
        cout << "[SMOKER " << s1 << "] Put ingredient" << endl;        
        table[s2] = (Ingredient) s2; 
        cout << "[SMOKER " << s2 << "] Put ingredient" << endl;
        print.V();
        smoker[s3].V(); // Wake third to make cigarette
        lock.V();

        if (arbiter.isZero()) {
            print.P();
            cout << "[ARBITER] Sleeping" << endl;
            print.V();
        }
        sleep(1);
        arbiter.P(); // Sleep Arbiter
        
    }
    sleep(3);
    exit(1);
} 

int main() {
    cout << "STARTED" << endl;
    // Three Smoker Process
    for (int i = 0; i < 3; i++) {
        pthread_create(&thread[i], NULL, Smoker, (void*)i);
    }
    sleep(1);
    // Arbiter Process
    pthread_create(&thread[4], NULL, Arbiter, NULL);
    
    for (int i = 0; i < 4; i++) {
        pthread_join(thread[i], NULL);
    }  
}