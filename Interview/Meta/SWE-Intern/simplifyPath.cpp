/*
cwd and target are inputs. return the final cwd.

cwd       target           return
/         a                /a
/b        /c               /c
/foo/bar  ../../../../..   /
/x/y      ../p/../q        /x/q
/x/y      /p/./q           /p/q
*/

#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

// Idea: keep the last dir in a stack
// If .. pop the last element. If . continue
// If new string, push in stack
// If first item is /, ignore input cwd.


vector<string> split (string s, char del) {
  if (s.length() == 0)
    return {};
  else if (s.length() == 1 && s[0] == '/')
    return {};
  vector<string> result;
  string tmp;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] != del) {
      tmp.push_back(s[i]);
    }
    else if (tmp.length() != 0) {
      result.push_back(tmp);
      tmp.clear();
    }
  }
  if (tmp.length() != 0)
    result.push_back(tmp);
  return result;
}

string finalPath (string cwd, string target) {
  stack<string> st;
  vector<string> cwds;
  if (target[0] != '/') {
    cwds = split (cwd, '/');
    for (auto & tmp : cwds) {
      st.push(tmp);
    }
  }

  cwds = split (target, '/');

  for (int i = 0; i < cwds.size(); i++) {
    if (cwds[i] == ".." && !st.empty())
        st.pop();
    else if (cwds[i] != ".")
        st.push(cwds[i]); // x q
  }

  string result;
  while(!st.empty()) {
    result = result + st.top() + "/";
    st.pop();
  }
  if (result.length() == 0)
    return "/";
  reverse(result.begin(), result.end());
  return result;
}

int main () {
  string cwd = "/x/y";
  string target = "../p/../q";
  cout << finalPath(cwd, target) << endl;
  return 0;
}
