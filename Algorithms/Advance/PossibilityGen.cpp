#include <iostream>
#include <string.h>
using namespace std;

void PrintRecurr(int num, int limit, int start, int end, char str[]) {
    if (num == limit) {
        cout << str << endl;
        return;
    }
    for (char i = start; i <= end; i++) {
        str[num] = i;
        PrintRecurr(num+1, limit, start, end, str);
    }
}

int main() {
   const int WIDTH = 3;
   char str[WIDTH+1] = {0};
   PrintRecurr(0, WIDTH, 'A', 'Z', str);
}