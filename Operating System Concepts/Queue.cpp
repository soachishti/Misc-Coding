#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

class Queue {
    public:
    Node *head, *tail;
    Queue () {
        head = NULL;
        tail = NULL;
    }
    void enqueue(int data) {
        Node *tmp = new Node;
        tmp->data = data;
        tmp->next = NULL;
        if (head == NULL) {
            tail = head = tmp;
        }
        else {
            tail->next = tmp;
            tail = tmp;
        }
    }
    
    Node dequeue() {
        Node tmp;
        if (head == tail) tail = NULL;
        if (head == NULL) {
            cout << "Queue Empty" << endl;
        }
        else {
            tmp = *head;
            delete head;
            head = tmp.next;
        }        
        return tmp;
    }
    
};

int main() {
    // Test
    /*
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.enqueue(6);
    
    for (int i = 0; i < 7; i++) {
        cout << q.dequeue().data << endl;
    }
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.enqueue(6);
    
    for (int i = 0; i < 7; i++) { 
        cout << q.dequeue().data << endl;
    }
    */
}