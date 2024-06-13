/* LC#71

Given a string path, 
which is an absolute path 
(starting with a slash '/') 
to a file or directory 
in a Unix-style file system, 
convert it to the simplified canonical path.

In a Unix-style file system, 
a period '.' refers to the current directory, 
a double period '..' refers to the directory up a level, 
and any multiple consecutive slashes (i.e. '//') 
are treated as a single slash '/'. 
For this problem, 
any other format of periods such as '...' 
are treated as file/directory names.

The canonical path should have the following format:

The path starts with a single slash '/'.
Any two directories are separated by a single slash '/'.
The path does not end with a trailing '/'.
The path only contains the directories 
on the path from the root directory 
to the target file or directory 
(i.e., no period '.' or double period '..')
Return the simplified canonical path.
*/

#include <iostream>
#include <string>
#include <stack>
using namespace std;


// beats ~91% LC users
string simplifyPath(string path) {
	vector<string> pp;
	string tmp = "";
	for (int i = 0; i < path.length(); i++) {
		if (path[i] != '/')
			tmp += path[i];
		else if (tmp != "") {
			pp.push_back(tmp);
			tmp.clear();
		}
	}
	if (tmp != "")
		pp.push_back(tmp);
	stack<string> st;
	for (auto &p : pp) {
		if (st.empty() && (p == ".." || p == "."))
			continue;
		else if (st.empty())
			st.push(p);
		else if (p == ".")
			continue;
		else if (p == "..")
			st.pop();
		else
			st.push(p);
	}
	tmp = "";
	while (!st.empty()) {
		tmp = "/" + st.top() + tmp;
		st.pop();
	}
    if (tmp == "")
        return "/";
	return tmp;
}

int main() {
	string path = "/../"; // "/home/../"; // "/home//foo/../"; // "/home//foo/";
	cout << simplifyPath (path) << endl;
	return 0;
}