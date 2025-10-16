#include <iostream>
using namespace std;

int main() {
    const int rows = 3;
    const int cols = 4;
    int arr[rows][cols] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // Sum of each row
    cout << "Row sums:\n";
    for (int i = 0; i < rows; ++i) {
        int rowSum = 0;
        for (int j = 0; j < cols; ++j) {
            rowSum += arr[i][j];
        }
        cout << "Row " << i << ": " << rowSum << endl;
    }

    // Sum of each column
    cout << "\nColumn sums:\n";
    for (int j = 0; j < cols; ++j) {
        int colSum = 0;
        for (int i = 0; i < rows; ++i) {
            colSum += arr[i][j];
        }
        cout << "Column " << j << ": " << colSum << endl;
    }

    return 0;
}