#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>


double getMedian(const std::vector<int>& vec) {
    std::vector<int> sortedVec = vec;  // Copy the vector to avoid modifying the original
    std::sort(sortedVec.begin(), sortedVec.end());  // Sort the vector

    int n = sortedVec.size();
    if (n % 2 == 0) {
        // If the number of elements is even, average the middle two elements
        return (sortedVec[n / 2 - 1] + sortedVec[n / 2]) / 2.0;
    } else {
        // If the number of elements is odd, return the middle element
        return sortedVec[n / 2];
    }
}


// Function to partition the vector around a pivot element
int partition(std::vector<int>& vec, int left, int right) {
    int pivot = vec[right];  // Choose the last element as the pivot
    int i = left - 1;  // Index of smaller element

    for (int j = left; j < right; j++) {
        if (vec[j] <= pivot) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }

    std::swap(vec[i + 1], vec[right]);
    return i + 1;
}

// Function to find the kth smallest element (based on quickselect)
int kthSmallest(std::vector<int>& vec, int left, int right, int k) {
    if (k > 0 && k <= right - left + 1) {
        int index = partition(vec, left, right);

        if (index - left == k - 1) {
            return vec[index];
        } else if (index - left > k - 1) {
            return kthSmallest(vec, left, index - 1, k);
        } else {
            return kthSmallest(vec, index + 1, right, k - index + left - 1);
        }
    }

    throw std::invalid_argument("Invalid k value.");
}

// Function to calculate the median of a vector without sorting
double getMedian(std::vector<int>& vec) {
    int n = vec.size();
    if (n % 2 == 0) {
        // If the number of elements is even, return the average of two middle elements
        int median1 = kthSmallest(vec, 0, n - 1, n / 2);
        int median2 = kthSmallest(vec, 0, n - 1, n / 2 + 1);
        return (median1 + median2) / 2.0;
    } else {
        // If the number of elements is odd, return the middle element directly
        return kthSmallest(vec, 0, n - 1, n / 2 + 1);
    }
}

int main() {
    std::vector<int> numbers = {5, 3, 8, 2, 9, 1, 7};
    double median = getMedian(numbers);
    std::cout << "Median: " << median << std::endl;

    return 0;
}
