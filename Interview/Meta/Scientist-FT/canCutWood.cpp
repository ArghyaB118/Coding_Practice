/*

We have n pieces of wood, 
with known lengths (integer array L). 
We need k smaller pieces of wood 
with equal length. 
What's the maximum integer length?

L=[5, 9, 7], k=3, return 5
_ _ _ _ _
_ _ _ _ _ | _ _ _ _
_ _ _ _ _ | _ _

L=[5, 9, 7], k=4, return 4 
_ _ _ _ | _
_ _ _ _ | _ _ _ _ | _
_ _ _ _ | _ _ _

*/

#include <iostream>
#include <vector>
using namespace std;

// O(n)
bool canCut (vector<int>& lengths, int k, int l) {
  if (l == 0)
    return true;
  int count = 0;
  for (auto &i : lengths) {
    count += (i / l);
    if (count >= k)
      return true;
  }
  return false;
}

// O(max(lengths) * n)
int maxLength (vector<int>& lengths, int k) {
  if (lengths.size() == 0)
    return 0;
  if (lengths.size() == 1)
    return lengths[0] / k;
  int left = 1;
  int right = *max_element(lengths.begin(), lengths.end());

  while (left < right) {
    if (right - left == 1) {
      bool can_cut_left = canCut(lengths, k, left);
      bool can_cut_right = canCut(lengths, k, right);
      if (can_cut_left && !can_cut_right) {
        return left;
      }
      else if (can_cut_left && can_cut_right) {
        return right;
      }
    }
    
    int mid = (left + right) / 2;
    if (canCut(lengths, k, mid))
      left = mid;
    else
      right = mid;
  }
  return -1;
}

int main () {
  vector<int> lengths= {5,9,7};
  int k = 4;
  cout << maxLength(lengths, k) << endl;
  return 0;
}