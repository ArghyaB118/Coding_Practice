/* LC#1011

A conveyor belt has packages 
that must be shipped from one port 
to another within days days.

The ith package on the conveyor belt 
has a weight of weights[i]. 
Each day, we load the ship with packages 
on the conveyor belt (in the order given by weights). 
We may not load more weight 
than the maximum weight capacity of the ship.

Return the least weight capacity of the ship 
that will result in all the packages 
on the conveyor belt being shipped within days days.
*/

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

// beats ~85% LC users
bool canShip (vector<int>& weights, int days, int capacity) {
	int cap = capacity;
	int d = 0;
	for (auto &w : weights) {
		if (cap - w < 0) { d++; cap = capacity; }
		cap -= w;
		if (cap < 0 || d > days)
			return false;
	}
	if (cap < capacity)
		d++;
	if (d > days)
		return false;
	return true;
}


int shipWithinDays(vector<int>& weights, int days) {
	int total_weight = accumulate(weights.begin(), weights.end(), 0);
	int left = 1, right = total_weight;

	while (left < right) {
		cout << left << " " << right << endl;
		if (right - left == 1 && canShip(weights, days, left))
			return left;
		else if (right - left == 1 && canShip(weights, days, right))
			return right;
		int mid = (left + right) / 2;
		if (canShip(weights, days, mid))
			right = mid;
		else
			left = mid;
	}

	return -1;
}

int main () {
	vector<int> weights = {1,2,3,4,5,6,7,8,9,10};
	int days = 5;
	cout << shipWithinDays(weights, days) << endl;
	return 0;
}