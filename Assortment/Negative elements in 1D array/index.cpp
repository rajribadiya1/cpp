#include <iostream>
using namespace std;

int main() {
    const int rows = 3;
    const int cols = 4;
    int arr[rows][cols] = {
        {3, 8, -2, 5},
        {7, 1, 0, 9},
        {-4, 6, 10, -1}
    };

    int maxElement = arr[0][0]; // Start with the first element

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (arr[i][j] > maxElement) {
                maxElement = arr[i][j];
            }
        }
    }

    cout << "Largest element: " << maxElement << endl;
    return 0;
}