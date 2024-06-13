/*
Given an array of integers,
count the number of contiguous subarrays,
so that each of these subarrays contain
k number of pairs of duplicates.
example:
for a subarray = {2 2 2}, number of pairs = 1
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int solution(vector<int> numbers, int k) {
    int n = numbers.size();
    int result = 0;
    for (int i = 0; i < n; i++) {
        int j = i;
        unordered_map<int, int> counts;
        while (j < n) {
            if (counts.find(numbers[j]) == counts.end())
                counts[numbers[j]] = 1;
            else {
                counts[numbers[j]]++;
            }
            
            // for (auto &c : counts)
            //    cout << c.first << " " << c.second << endl;
            
            int num_pairs = 0;
            for (auto &c : counts) {
                if (c.second > 1) {
                    num_pairs += (c.second / 2);  // (c.second * (c.second - 1) / 2);
                }
            }
            if (num_pairs >= k) {
                result += (n - j);
                j = n;
            }
            
            j++;
        }
        counts.clear();
    }
    return result;
}

int main () {
    vector<int> numbers = {1, 2, 2, 5, 4, 2, 4, 2, 7};
    cout << solution(numbers, 2) << endl;
    return -1;
}
