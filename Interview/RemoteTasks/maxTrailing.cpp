/*
max of ther difference an element
and the minimum from the left.
if no such element, return -1.
*/

#include <iostream>
#include <vector>
using namespace std;

int maxTrailing(vector<int> arr) {
    int result = -1;
    if (arr.size() == 1)
        return result;
    int min_left = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > min_left)
            result = max(result, arr[i] - min_left);
        else if (arr[i] < min_left)
            min_left = arr[i];
    }
    return result;
}

int main () {
    vector<int> arr = {2, 3, 4, 7, 4, 1};
    cout << maxTrailing(arr) << endl;
    return -1;
}