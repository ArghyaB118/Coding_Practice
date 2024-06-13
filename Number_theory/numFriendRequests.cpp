/* LC#825

There are n persons on a social media website. 
You are given an integer array ages 
where ages[i] is the age of the ith person.

A Person x will not send a friend request 
to a person y (x != y) 
if any of the following conditions is true:

age[y] <= 0.5 * age[x] + 7
age[y] > age[x]
age[y] > 100 && age[x] < 100
Otherwise, 
x will send a friend request to y.

Note that if x sends a request to y, 
y will not necessarily send a request to x. 
Also, a person will not send 
a friend request to themself.

Return the total number of friend requests made.
*/

// returns the index of the first element with value `val`
int binary_search1 (int val, vector<int>& ages) {
	int left = 0, right = ages.size() - 1;
	while (left < right) {
		if (right - left == 1 && ages[left] >= val)
			return left;
		else if (right - left == 1 && ages[left] < val)
			return right;

		int mid = (left + right) / 2;
		if (ages[mid] < val)
			left = mid;
		else if (ages[mid] >= val)
			right = mid;
	}
	return -1;
}

// returns the index of the last element with value `val`
int binary_search2 (int val, vector<int>& ages) {
	int left = 0, right = ages.size() - 1;
	while (left < right) {
		if (right - left == 1 && ages[right] > val)
			return left;
		else if (right - left == 1 && ages[right] == val)
			return right;

		int mid = (left + right) / 2;
		if (ages[mid] > val)
			right = mid;
		else if (ages[mid] <= val)
			left = mid;
	}
	return -1;
}

int numFriendRequests(vector<int>& ages) {
	sort(ages.begin(), ages.end());
    for (auto &i : ages)
        cout << i << " ";
    cout << endl;
	int n = ages.size();
	int count = 0;
	for (int i = 0; i < n; i++) {
		int y = ages[i];
        
		int yy = min((int)(y * 0.5 + 7 + 1), y);
        cout << yy << endl;
		int left = binary_search1(yy, ages);
		int right = binary_search2(y, ages);
        cout << left << " " << right << endl;
		count += (right - left);
        cout << count << endl;
	}
	return count;
}
