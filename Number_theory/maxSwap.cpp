/* LC#670

You are given an integer num. 
You can swap two digits at most once 
to get the maximum valued number.

Return the maximum valued number 
you can get.
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef pair<int, int> p;

struct comp {
	bool operator()(p a, p b) {
		if (a.first != b.first)
			return a.first > b.first;
		else
			return a.second < b.second;
	}
};

// WRONG: fails for input 98868
int maximumSwap2(int num) {
	stack<int> q;
	vector<p> v;
	int i = 1;
	while (num > 0) {
		v.push_back({num % 10, i});
		q.push(num % 10);
		num /= 10; i++;
	}
	comp c;
	sort(v.begin(), v.end(), c);
	for (auto &i : v)
		cout << i.first << " " << i.second << endl;
	int result = 0, swap_index = 0, swap_value = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].first == q.top()) {
			result = result * 10 + q.top();
			q.pop();
		}
		else {
			swap_index = v[i].second;
			swap_value = q.top();
			result = result * 10 + v[i].first;
			q.pop();
			break;
		} 
	}
	cout << result << " " << swap_value << " " << swap_index << endl;
	if (q.empty()) { return result; }
	while (q.size() > swap_index) {
		result = result * 10 + q.top();
		q.pop();
	}
	result = result * 10 + swap_value; q.pop();
	while (!q.empty()) {
		result = result * 10 + q.top();
		q.pop();
	}
	return result;
}

// beats 100% LC users
int maximumSwap(int num) {
	int result = num;
	vector<int> v;
	while (num > 0) {
		v.push_back(num % 10);
		num /= 10;
	}
	reverse(v.begin(), v.end());
	vector<int> u = v;
	sort(u.begin(), u.end(), greater<int>());
	if (u == v)
		return result;
	for (int &i : u)
		cout << i << " ";
	cout << endl;
	for (int &i : v)
		cout << i << " ";
	cout << endl;
	result = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] != u[i]) {
			for (int j = v.size() - 1; j >= 0; j--) {
				if (v[j] == u[i]) {
					cout << i << " " << j << endl;
					swap(v[i], v[j]);
					for (int &i : v) {
						result = result * 10 + i;
					}
					return result;
				}
			}
		}
	}
	return result;	
}


int main () {
	cout << maximumSwap (937903) << endl; //  9973 9937 98368 2736 99345125
	return 0;
}