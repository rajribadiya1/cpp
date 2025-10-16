#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> arr = {3, -1, 4, -5, 0, -2};
    std::vector<int> negative_elements;

    std::copy_if(arr.begin(), arr.end(), std::back_inserter(negative_elements),
                 [](int x) { return x < 0; });

    for (int x : negative_elements)
        std::cout << x << " ";  // Output: -1 -5 -2
}