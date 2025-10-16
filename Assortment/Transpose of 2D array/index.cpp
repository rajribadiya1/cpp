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

    // Transposed array will have dimensions [cols][rows]
    int transposed[cols][rows];

    // Transpose logic
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = arr[i][j];
        }
    }

    // Display transposed array
    cout << "Transposed array:\n";
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            cout << transposed[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}