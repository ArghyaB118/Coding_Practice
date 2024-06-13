// QUESTION

// Given an array of integers that represent the height of buildings.
// Where left most building is in index 0 and the array lists the buildings from left to right. 
// After the rightmost building, we hit the ocean.
// Buildings are of the same width and in a straight line from left to right towards the ocean.

// --> Return the indexes of the buildings that have ocean view
// [2, 3, 4, 2, 1]
// [4, 3, 2]
// [2, 3, 4]

// []
// [2]
// [2, 3, 4, 2, 2, 1]

#include <iostream>
#include <vector>
using namespace std;

vector<int> oceanview (vector<int>& heights) {
  if (heights.size() == 0)
    return {};
  else if (heights.size() == 1)
    return {0};
  
  vector<int> result;
  int curr_max = heights.back();
  result.push_back(heights.size() - 1);
  for (int i = heights.size() - 2; i >= 0; i--) {
    if (heights[i] > curr_max)
      result.push_back(i);
    curr_max = max(curr_max, heights[i]);
  }

  vector<int> reversed_result;
  for (int i = result.size() - 1; i >= 0; i--) {
    reversed_result.push_back(result[i]);
  }
  return reversed_result;
}

int main () {
  vector<int> heights = {2, 3, 4, 2, 2, 1};
  vector<int> result = oceanview(heights);
  for (auto &i : result)
    cout << i << " ";
  cout << endl;
	return 0;
}