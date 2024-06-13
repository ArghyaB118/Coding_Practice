/*
Given a string of digits `s`, introduce '+' or '-'
anywhere in the string to make the resultant number `target`.

Example:
string = -123456789
target = 100

Allowed: +, - 

+1+2+3-4+5+6+8+79
+1+2+34-5+67-8+9
+1+23-4+5+6+78-9
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

int findIndexAfterK (string s, int k) {
	int i = 0;
	while (k > 0) {
		if (isdigit(s[i])) {
			k--; i++;
		}
		else { i++; }
	}
	return i;
}

bool evaluate (string s, string t) {
	return true;
}

vector<string> sumToTarget (string s, string target) {
	unordered_set<string> ss;
	ss.insert(s);
	int k = 0;
	// cout << "here" << endl;
	for (int i = 0; i < s.length(); i++) {
		// cout << i << ss.size() << endl;
		vector<string> tmp = {};
		for (auto &sss : ss) {
			int idx = findIndexAfterK(sss, i);
			// cout << idx << endl;
			if (i != 0) {
				string sss_copy = sss;
				sss_copy.insert(idx, "+");
				tmp.push_back(sss_copy);
			}
			// cout << "hefrt" << endl;
			string sss_copy = sss;
			sss_copy.insert(idx, "-");
			// cout << sss_copy << endl;
			tmp.push_back(sss_copy);
		}
		for (auto &tmp_ : tmp) {
			ss.insert(tmp_);
		}
	}
	vector<string> result = {};
	for (auto sss : ss) {
		// cout << sss << endl;
		if (evaluate (sss, target))
			result.push_back(sss);
	}
	return result;
}

int main () {
	string s = "1234", t = "100";
	vector<string> res = sumToTarget (s, t);
	for (auto &ss : res)
		cout << ss << endl;
	return 0;
}