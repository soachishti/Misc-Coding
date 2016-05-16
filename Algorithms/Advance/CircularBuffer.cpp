#include <iostream>
using namespace std;

int kb_buffer_size = 3;
char kb_buffer[3];
int kb_buffer_read = 0;
int kb_buffer_write = 0;

void add_to_buffer(char value, char buffer[], int &write, int &read, int size) {
    if (read == (write + 1) % size) {
        cout << "Buffer Full" << endl;
        return; // Buffer full
    }
    cout << "Adding - " << (write + 1) % size << endl;
    buffer[write] = value;
    write = (write + 1) % size;
}

char get_from_buffer(char buffer[], int &write, int &read, int size) {
    char ch;
    if (read == write) {
        cout << "Buffer empty" << endl;
        return 0;
    }
    ch = buffer[read];
    read = (read + 1) % size;
    return ch;
}

int main() {
    add_to_buffer('1', kb_buffer, kb_buffer_write, kb_buffer_read, kb_buffer_size);
    add_to_buffer('2', kb_buffer, kb_buffer_write, kb_buffer_read, kb_buffer_size);
    add_to_buffer('3', kb_buffer, kb_buffer_write, kb_buffer_read, kb_buffer_size);
    add_to_buffer('4', kb_buffer, kb_buffer_write, kb_buffer_read, kb_buffer_size);
    add_to_buffer('5', kb_buffer, kb_buffer_write, kb_buffer_read, kb_buffer_size);
    cout << get_from_buffer(kb_buffer, kb_buffer_write, kb_buffer_read, kb_buffer_size) << endl;
    cout << get_from_buffer(kb_buffer, kb_buffer_write, kb_buffer_read, kb_buffer_size) << endl;
    
}