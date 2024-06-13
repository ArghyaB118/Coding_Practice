/* LC#973

K cLosest points
Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct point {
	int x, y;
	double dist;
};

struct cmp {
	bool operator() (const point& p, const point& q) {
		return p.dist < q.dist;
	}
};

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
	priority_queue<point, vector<point>, cmp> pq;
	for (int i = 0; i < k; i++)
		pq.push({points[i][0], points[i][1], sqrt(points[i][0]*points[i][0] + points[i][1]*points[i][1])});

	for (int i = k; i < points.size(); i++) {
		pq.push({points[i][0], points[i][1], sqrt(points[i][0]*points[i][0] + points[i][1]*points[i][1])});
		pq.pop();
	}
	points.clear();

	while (!pq.empty()) {
		struct point tmp = pq.top();
//		cout << tmp.x << tmp.y << tmp.dist << endl;
		pq.pop();
		points.push_back({tmp.x, tmp.y});
	}
	return points;
}

struct pp {
	int x, y;
};

struct comp {
	bool operator() (const pp& p, const pp& q) {
		return ((p.x * p.x + p.y * p.y) < (q.x * q.x + q.y * q.y));
	}
};

vector<vector<int>> kClosestOptimized (vector<vector<int>>& points, int k) {
	priority_queue<pp, vector<pp>, comp> pq;
	for (int i = 0; i < k; i++)
		pq.push({points[i][0], points[i][1]});

	for (int i = k; i < points.size(); i++) {
		pq.push({points[i][0], points[i][1]});
		pq.pop();
	}
	points.clear();

	while (!pq.empty()) {
		struct pp tmp = pq.top();
//		cout << tmp.x << tmp.y << tmp.dist << endl;
		pq.pop();
		points.push_back({tmp.x, tmp.y});
	}
	return points;
}

// beats ~98% LC users
typedef pair<int, int> point;
struct cmp {
	bool operator() (const point &a, const point &b) {
		return a.first * a.first + a.second * a.second > b.first * b.first + b.second * b.second;
	};
};

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
	vector<vector<int>> result;
	priority_queue<point, vector<point>, cmp> pq;
	for (int i = 0; i < points.size(); i++)
		pq.push({points[i][0], points[i][1]});
	while (k > 0) {
		result.push_back({pq.top().first, pq.top().second});
		pq.pop(); k--;
	}
	return result;
}

typedef pair<int, int> Pair;
struct cmp {
	bool operator() (const Pair &a, const Pair &b) {
		return a.first < b.first;
	};
};

void kClosest(int array[], int size, int x, int k) {
	priority_queue<Pair, vector<Pair>, cmp> pq;
	for (int i = 0; i < k; ++i) {
		pq.push({abs(array[i] - x), i});
	}
	for (int i = k; i < size; ++i) {
		int diff = abs(array[i] - x);
		if (diff < pq.top().first) {
			pq.pop();
			pq.push({diff, i});
		}
	}
	while (!pq.empty()) {
		cout << array[pq.top().second] << ' ';
		pq.pop();
	}
}

/* LC#658

Given a sorted integer array arr, 
two integers k and x, 
return the k closest integers to x in the array. 
The result should also be sorted in ascending order.
*/

int binary_search (vector<int>& arr, int x) {
	if (x <= arr[0])
		return 0;
	else if (arr.back() <= x)
		return arr.size() - 1;

	int left = 0, right = arr.size() - 1;
	while (left < right) {
		if (right - left == 1 && arr[left] >= x)
			return left;
		else if (right - left == 1 && arr[left] < x && arr[right] >= x)
			return right;
		int mid = (left + right) / 2;
		if (arr[mid] == x)
			return mid;
		else if (arr[mid] < x)
			left = mid;
		else if (arr[mid] > x)
			right = mid;
	}
    return -1;
}

vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int n = arr.size();
    if (n == k)
        return arr;

	int index = binary_search(arr, x);
    vector<int> result;
    if (index == 0) {
        for (int i = 0; i < k; i++)
            result.push_back(arr[i]);
        return result;
    }
    else if (index == n - 1) {
        for (int i = n - k; i < n; i++)
            result.push_back(arr[i]);
        return result;
    }

	int left = index - 1, right = index;
    
    cout << left << " " << right << endl;
	while (left >= 0 && right < n && k > 0) {
        if (left == 0)
            right++;
        else if (right == n - 1)
            left--;
		else if (abs(arr[left] - x) <= abs(arr[right] - x))
			left--;
		else if (abs(arr[left] - x) > abs(arr[right] - x))
			right++;
		k--;
	}
	cout << left << " " << right << endl;
    if (right - left == k && abs(arr[left] - x) <= abs(arr[right] - x))
        right--;
    else if (right - left == k && abs(arr[left] - x) > abs(arr[right] - x))
        left++;
    
    for (int i = left; i <= right; i++)
        result.push_back(arr[i]);
    return result;
}


int main () {
	vector<vector<int>> points = {{3,3},{5,-1},{-2,4}};
	int k = 2;
	kClosest(points, k);
	for (auto & p : points)
		cout << p[0] << " " << p[1] << endl;

	points.clear();
	points = {{3,3},{5,-1},{-2,4}};
	kClosestOptimized(points, k);
	for (auto & p : points)
		cout << p[0] << " " << p[1] << endl;

	int array[] = {-10, -50, 20, 5, 67, 54, -3};
	int x = 20, k = 3;
	int sizeofarray = sizeof(array) / sizeof(array[0]);
	kClosest(array, sizeofarray, x, k); 

	return 0;
}