// Longest Common Subsequence

#include <iostream>
#include <cstdlib>
using namespace std;

void LCS(string a, string b) {
    int m = a.size();
    int n = b.size();
    int **c = new int*[m];
    for (int i = 0; i < m; i++) {
        c[i] = new int[n];
    }
    // Finding length
    for (int i = 0; i < n; i++) c[0][i] = 0;
    for (int i = 0; i < m; i++) c[i][0] = 0;
    for (int i = 1; i < m; i++) 
    {
        for (int j = 1; j < n; j++) {
            if (a[i] == a[j]) 
                c[i][j] = c[i-1][j-1] + 1;
            else 
                c[i][j] = max(c[i-1][j], c[i][j-1]);
        }
    }
    
    // Finding sub sequence using table
    cout << "String: ";
    for (int i = m-1; i > 1; ) 
    {
        for (int j = n-1; j > 1; ) {
            if (c[i][j] == c[i-1][j]) {
                i--;
            }
            else {
                cout << a[i];
                i--;
                j--;
            }
        }
    }
    cout << endl
         << "String Size: " << c[m-1][n-1] << endl;
    return;  
}

int main() {
    string a = "ABCB";
    string b = "BDCAB";
    LCS(a,b);
}