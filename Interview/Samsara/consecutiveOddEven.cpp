/*
Given an array of integers,
if there are two consecutive integers,
where both are odd or both are even,
return the index of the later index.
If there is no such pair, return -1.

E.g. 1: nums = {1 2 3 4}, output = -1
E.g. 2: nums = {1 2 4 3 8 5} output = 2
*/

#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> numbers) {
    int n = numbers.size();
    if (n == 1)
        return -1;
    for (int i = 1; i < n; i++) {
        if (numbers[i] % 2 == 0 && numbers[i - 1] % 2 == 0)
            return i;
        else if (numbers[i] % 2 != 0 && numbers[i - 1] % 2 != 0)
            return i;
    }
    return -1;
}

int main () {
    vector<int> nums = {1, 2, 4, 3, 8, 5};
    cout << solution (nums) << endl;
    return -1;
}
