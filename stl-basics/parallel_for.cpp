#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Using std::for_each with std::execution::par policy for parallel execution
    std::for_each(std::execution::seq, vec.begin(), vec.end(), [](int& num) {
        num *= 2;  // Double each element in parallel
    });

    // Print the modified vector
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
