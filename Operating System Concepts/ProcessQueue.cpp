#define NULL 0

struct Process {
    int id;
    char name[16];
    int status;
};

struct Node {
    Process *data;
    Node *next = NULL;
};

class Queue {
    public:
    Node *head, *tail;
    Queue () {
        head = NULL;
        tail = NULL;
    }
    
    void enqueue(Process* data) {
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
    
    Node* dequeue() {
        Node *tmp;
        if (head == tail) tail = NULL;
        if (head == NULL) {
            return NULL;
        }
        else {
            tmp = head;
            delete head;
            head = tmp->next;
        }        
        return tmp;
    }
    
};

struct ProcessManagement {
    Queue Ready;
    Queue EventFile;
    Queue EventNetwork;
    Queue EventDevice;
    Process *Running;
    
    // Timeout Interrupt Routine
    void interruptTimeout() {
        Ready.enqueue(Running);
        next();
    }

    void interruptFile(Process *intProcess) {
        Ready.enqueue(intProcess);
        next();
    }

    void interruptNetwork(Process *intProcess) {
        Ready.enqueue(intProcess);
        next();
    }    

    void interruptDevice(Process *intProcess) {
        Ready.enqueue(intProcess);
        next();
    }    
    
    Process* next() {
        Running = Ready.dequeue()->data;
    }
};

int main() {
    Process *chrome;
    Process *chrome1;
    Process *chrome2;
    Process *chrome3;
    Process *Adobe;
    Process *Notepad;
    
    ProcessManagement Manager;
    
    Manager.Running = chrome;
    Manager.Ready.enqueue(Adobe);
    Manager.Ready.enqueue(Notepad);
    Manager.EventFile.enqueue(chrome1);
    Manager.EventNetwork.enqueue(chrome2);
    Manager.EventDevice.enqueue(chrome3);
    
    while(true) {
        Manager.next();
        // Process in Manager.Running
    }
    
    return 0;
}