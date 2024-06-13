#include <iostream>
using namespace std;

// Run length encoding
// O(n)
string encode(string str) {
	if (str == "")
		return "";
	char prevChar = str[0];
	string output = "";
	int count = 1;
	for (int i = 1; i < str.length(); i++) {
		if (str[i] != prevChar) {
			output.append(to_string(prevChar)); output.append(to_string(count)); 
			count = 1; prevChar = str[i];
		}
		else {
			count++;
		}
	}
	return output;
}

// Run length decoding
// O(m)
void decode(string str) {
	string output = "";
	if (str == "")
		return;
	cout << str << str.length() << endl;
	for (int i = 0; i < str.length() / 2; i++)
		for (int j = 0; j < str[2*i + 1]; j++)
			output.push_back(str[2*i]);
	cout << output;
}

void print(string str) {
	cout << str << endl;
}

/* LC#1868

Product of two run-length encoded arrays
*/


vector<int> decoder (vector<vector<int>>& encoded) {
	vector<int> decoded;
	for (int i = 0; i < encoded.size(); i += 2) {
		for (int j = 0; j < encoded[i][1]; j++)
			decoded.push_back(encoded[i][0]);
	}
	return decoded;
}

vector<vector<int>> encoder (vector<int>& nums) {
	vector<vector<int>> result;
	int i = 0, tmp = nums[0], count = 1;
	while (i < nums.size()) {
		if (nums[i] == tmp)
			count++;
		else {
			result.push_back({tmp, count});
			tmp = nums[i];
			count = 1;
		}
	}
	if (count > 0)
		result.push_back({tmp, count});
	return result;
}

vector<vector<int>> findRLEArray
(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
	vector<int> nums1 = decoder(encoded1);
	vector<int> nums2 = decoder(encoded2);
	int n = nums1.size();
	for (int i = 0; i < n; i++) {
		nums1[i] = nums1[i] * nums2[i];
	}
	return encoder(nums1);
}

int main() {
	string str = "uvxxxyyyyzzzzvvvvy"; print(str);
	cout << encode(str) << endl; string str2 = "w4u2";
	decode(str2);
	return 0;
}