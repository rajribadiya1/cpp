#include <bits/stdc++.h>
using namespace std;

// Selection Sort: Finds min in unsorted part and swaps [web:2][page:2]
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        swap(arr[i], arr[min_idx]);
    }
}

// Merge function for Merge Sort [page:1]
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort: Recursive divide-conquer-merge [web:3][page:1]
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Binary Search: On sorted array [web:8][web:12]
int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void printArray(const vector<int>& arr) {
    for (int val : arr) cout << val << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    cout << "Original: "; printArray(arr);

    // Category 1: Simple Selection Sort
    vector<int> sel = arr;
    selectionSort(sel);
    cout << "Selection Sorted: "; printArray(sel);

    // Category 2: Divide-Conquer Merge Sort
    vector<int> mer = arr;
    mergeSort(mer, 0, mer.size() - 1);
    cout << "Merge Sorted: "; printArray(mer);

    // Category 3: Search on Sorted (using merge sorted)
    int target = 22;
    int idx = binarySearch(mer, target);
    cout << "Binary Search " << target << " at index: " << idx << endl;

    return 0;
}
