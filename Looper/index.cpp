#include <iostream>
using namespace std;

int main() {
    char ch = 'A';
    int count = 1;

    while (ch <= 'Z') {
        if (count % 3 != 0) {
            cout << ch << " ";
        }
        ch++;
        count++;
    }

    return 0;
}