/* LC#394

Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].

The test cases are generated so that the length of the output will never exceed 105.

Input: s = "3[a]2[bc]"
Output: "aaabcbc"

Input: s = "3[a2[c]]"
Output: "accaccacc"

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"*/

#include <iostream>
#include <string>
using namespace std;

string decodeStringNotQuite (string s) {
	int tmpnum = 0;
	string tmp = "", result = "";
	for (auto& ch : s) {
		if (ch >= 48 && ch <= 57)
			tmpnum = tmpnum * 10 + ((int)ch - 48);
		else if (ch == '[')
			tmp.clear();
		else if (ch == ']') {
			for (int i = 0; i < tmpnum; i++)
				result += tmp;
			tmp.clear(); tmpnum = 0;
		}
		else
			tmp.push_back(ch);
	}
	return result;
}

/* 2[a3[b4[c]]de] 
stack<int> {2, 3, 4} => {2, 3} => {2}
stack<string> {a, b, c} => {a, bcccc} => {abccccbccccbcccc + de}*/

string decodeString (string s) {
	stack<int> tmpnum;
	stack<string> tmp;
	int tmpnum = 0;
	string tmp = "";
	bool newNum = true;
	for (auto& ch : s) {
		if (ch >= 48 && ch <= 57) {
			if (tmpnum.empty() || newNum) {
				tmpnum.push((int)ch - 48);
				newNum = false;
			}
			else
				tmpnum.top() = tmpnum.top() * 10 + ((int)ch - 48);
		}
		else if (ch == '[') {
			newNum = true;
		}
	}
}

string decodeString (string s) {
	bool is_ready = true;
	for (auto &ch: s) {
		if (ch == '[') {
			is_ready = false;
			break;
		}
	}
	if (is_ready) { return s; }
	string res = "";
	vector<int> start_indices, end_indices;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '[')
			start_indices.push_back(i);
		else if (s[i] == ']')
			end_indices.push_back(i);
	}
}

int main () {
	string s = "3[a]2[bc]";
	cout << decodeString(s) << endl;
}