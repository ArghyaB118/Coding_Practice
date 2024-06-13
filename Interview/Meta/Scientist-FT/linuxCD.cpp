/* 

make a linux cd function.

| cwd      | cd (arg)       | output
| -------- | -------------- | ------
| /        | foo            | /foo
| /baz     | /bar           | /bar
| /foo/bar | ../../../../.. | /
| /x/y     | ../p/../q      | /x/q
| /x/y     | /p/./q         | /p/q

dyan@meta.com
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

vector<string> splitter (string dir, char split_char) {
	vector<string> dir_ = {};
	string tmp = "";
	for (auto &ch : dir) {
		if (ch == split_char) {
			if (tmp != "")
				dir_.push_back(tmp);
			tmp.clear();
		}
		else
			tmp.push_back(ch);
	}
	if (tmp != "")
		dir_.push_back(tmp);
	return dir_;
}

string changeDir (string cwd, string cd) {
	if (cd == "")
		return cwd;
	vector<string> cd_ = splitter(cd, '/');
	// for (auto &s : cd_)
	// 	cout << s << endl;
	
	vector<string> cwd_ = {};
	if (cd[0] != '/') {
		cwd_ = splitter(cwd, '/'); 
		// cout << endl;
		// for (auto &s : cwd_)
		// 	cout << s << endl;
	}

	stack<string> st;
	for (auto &s : cwd_) {
		st.push(s);
	}
	// cout << st.size() << endl;
	for (auto &s : cd_) {
		// cout << st.size() << endl;
		if (s == ".." && st.empty())
			continue;
		else if (s == ".." && !st.empty())
			st.pop();
		else if (s == ".")
			continue;
		else
			st.push(s);
	}
	// cout << st.size() << endl;
	string res = "";
	while (!st.empty()) {
		res = "/" + st.top() + res;
		st.pop();
	}
	return res;
}

int main () {
	string cwd = "/x/y", cd = "../p/../q";
	cout << changeDir(cwd, cd) << endl;
	return 0;
}