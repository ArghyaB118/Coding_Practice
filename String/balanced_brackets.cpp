/*
Balance Brackets

A bracket is any of the following characters: (, ), {, }, [, or ].

We consider two brackets to be matching if the first bracket is an open-bracket, 
e.g., (, {, or [, and the second bracket is a close-bracket of the same type. 
That means ( and ), [ and ], and { and } are the only pairs of matching brackets.
Furthermore, a sequence of brackets is said to be balanced if the following 
conditions are met:
	The sequence is empty, or
	The sequence is composed of two or more non-empty sequences, 
	all of which are balanced, or
	The first and last brackets of the sequence are matching, 
	and the portion of the sequence without the first and last elements is balanced.

You are given a string of brackets. Your task is to determine whether 
each sequence of brackets is balanced. If a string is balanced, return true, 
otherwise, return false.

Example 1
s = {[()]}
output: true
Example 2
s = {}()[]
output: true
Example 3
s = {(})
output: false
Example 4
s = ){
output: false
Example 5
s = {[(])}
output: false
Example 6
s = {{[[(())]]}}
output: true
*/

#include <iostream>
#include <string>
#include <stack>
using namespace std;

// The following function fails for "()[]{}"
bool isBalanced(string s) {
    if(s.length() == 0)
        return true;
    if (s.length() % 2 != 0)
        return false;
    stack<char> st;
    for (int i = 0; i < s.length(); i++)
        st.push(s[i]);
    for (int i = 0; i < s.length() / 2; i++) {
        if (s[i] == '(' && st.top() == ')')
            st.pop();
        else if (s[i] == '{' && st.top() == '}')
            st.pop();
        else if (s[i] == '[' && st.top() == ']')
            st.pop();
        else
            return false;
    }
    return true;
}

bool isBalanced(string s) {
    if(s.length() == 0)
        return true;
    if (s.length() % 2 != 0)
        return false;
    stack<char> st;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            st.push(s[i]);
        else if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
            if (st.empty())
                return false;
            if ((s[i] == ')' && st.top() == '(') || (s[i] == '}' && st.top() == '{') || (s[i] == ']' && st.top() == '['))
                st.pop();
            else
                return false;
        }
    }
    if (!st.empty())
        return false;
    return true;
}


// These are the tests we use to determine if the solution is correct.
// You can add your own at the bottom.

void printString(string& str) {
  cout << "[\"" << str << "\"]";
}

int test_case_number = 1;

void check(bool expected, bool output) {
  bool result = (expected == output);
  const char* rightTick = u8"\u2713";
  const char* wrongTick = u8"\u2717";
  if (result) {
    cout << rightTick << "Test #" << test_case_number << "\n";
  }
  else {
    cout << wrongTick << "Test #" << test_case_number << ": Expected ";
    printf("%s", expected ? "true" : "false");
    cout << " Your output: ";
    printf("%s", output ? "true" : "false");
    cout << endl; 
  }
  test_case_number++;
}

// (())
//(0001
//( 010
//)  00
//)   0
int longestValidParentheses (string s) {
  bool dp[s.length()][s.length()];
  int max_length = 0, j = 0;
  for (int i = 0; i < s.length(); i++) {
    while (j <= i) {
      dp[i][j] = false; j++;
    }

    if ((j = i + 1) && (j < s.length()) && (s[i] == '(') && (s[j] == ')')) {
      dp[i][j] = true;
      max_length = max(2, max_length);
    }
  }

  for (int i = s.length() - 3; i >= 0; i--) {
    for (j = 0; j < s.length(); j++) {
      if (s[i] == '(' && s[j] == ')') {
        dp[i][j] = true;
        max_length = max(max_length, j - i + 1);
      }
    }
  }
  return max_length;
}

/* LC#1249

Minimum Remove to Make Valid Parentheses

Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', 
in any positions ) so that the resulting parentheses string is valid 
and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"

Input: s = "a)b(c)d"
Output: "ab(c)d"

Input: s = "))(("
Output: ""
*/

typedef pair<char, int> Pair;

// Idea: Maintain a stack of opening parentheses and their positions.
// As you see the corresponding closing parentheses, pop the stack
// At the end, remove the parentheses left in the stack one by one from the string
string minRemoveToMakeValid (string s) {
    stack<Pair> st;
    for (int i = 0; i < s.length(); i++) {
        if (!isalpha(s[i])) {
            if (st.empty())
                st.push(make_pair(s[i], i));
            else {
                if (s[i] == '(')
                    st.push(make_pair(s[i], i));
                else if (s[i] == ')' && st.top().first == '(')
                    st.pop();
                else if (s[i] == ')' && st.top().first != '(')
                    st.push(make_pair(s[i], i));
            }
        }
    }
    
    while (!st.empty()) {
        Pair tmp = st.top(); st.pop();
        s.erase(s.begin() + tmp.second);
    }
    return s;
}

// beats ~30% LC users
string minRemoveToMakeValidOptimized (string s) {
    stack<int> st;
    for (int i = 0; i < s.length(); i++) {
        if (!isalpha(s[i])) {
            if (st.empty())
                st.push(i);
            else {
                if (s[i] == '(')
                    st.push(i);
                else if (s[i] == ')' && s[st.top()] == '(')
                    st.pop();
                else if (s[i] == ')' && s[st.top()] != '(')
                    st.push(i);
            }
        }
    }
    
    unordered_set<int> index_for_deletion;
    while (!st.empty()) {
        index_for_deletion.insert(st.top());
        st.pop();
    }
    string res = "";
    for (int i = 0; i < s.length(); i++) {
        if (index_for_deletion.find(i) == index_for_deletion.end())
            res.push_back(s[i]);
    }
    return res;
}

/*
vector<string> removeInvalidParentheses (string s) {
  int left = 0, right = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '(')
      left++;
    else if (s[i] == ')' && left != 0)
      left--;
    else if (s[i] == ')' && left == 0)
      right++;
  }
}
*/

/* LC#921

Minimum Add to Make Parentheses Valid

A parentheses string is valid if and only if:

It is the empty string,
It can be written as AB (A concatenated with B), 
where A and B are valid strings, or
It can be written as (A), where A is a valid string.
You are given a parentheses string s. In one move, 
you can insert a parenthesis at any position of the string.

For example, if s = "()))", 
you can insert an opening parenthesis to be "(()))" 
or a closing parenthesis to be "())))".
Return the minimum number of moves required to make s valid.
*/

int minAddToMakeValid(string s) {
    stack<char> st;
    for (int i = 0; i < s.length(); i++) {
        if (!st.empty() && s[i] == ')' && st.top() == '(')
          st.pop();
        else
          st.push(s[i]);
    }
    return st.size();
}

// beats ~50% LC users
int minAddToMakeValidOptimized (string s) {
    int open = 0, count = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') open++;
        else if (s[i] == ')')
            (open > 0) ? open-- : count++; 
    }
    count += open;
    return count;
}

/* LC#1541

Given a parentheses string s containing only the characters '(' and ')'. 
A parentheses string is balanced if:

Any left parenthesis '(' must have a corresponding 
two consecutive right parenthesis '))'.
Left parenthesis '(' must go before the corresponding 
two consecutive right parenthesis '))'.
In other words, we treat '(' as an opening parenthesis 
and '))' as a closing parenthesis.

For example, "())", "())(())))" and "(())())))" are balanced, 
")()", "()))" and "(()))" are not balanced.
You can insert the characters '(' and ')' at any position 
of the string to balance it if needed.

Return the minimum number of insertions needed to make s balanced.
*/

int minInsertions(string s) {
    stack<char> st;
    int count = 0, i = 0;
    while (i < s.length()) {
        if (s[i] == '(' && (st.empty() || st.top() == '('))
            st.push(s[i]);

        else if (s[i] == '(' && st.top() == ')') {
            st.pop(); 
            if (st.empty())
                count += 2;
            else if (st.top() == ')') {
                st.pop(); count++;
            }
            else if (st.top() == '(') {
                st.pop(); count++;
            }
        }

        else if (s[i] == ')' && (st.empty() || st.top() == '('))
            st.push(s[i]);

        else if (s[i] == ')' && st.top() == ')') {
            st.pop();
            if (st.empty())
                count++;
            else if (st.top() == '(')
                st.pop();
        }

        i++;
    }
    if (!st.empty() && st.top() == ')') {
        st.pop();
        if (st.empty())
            count += 2;
        else if (st.top() == '(') {
            st.pop(); count++;
        }
    }
    while (!st.empty()) {
        st.pop(); count += 2;
    }
    return count;
}

/* LC#1614

A string is a valid parentheses string (denoted VPS) 
if it meets one of the following:

It is an empty string "", 
or a single character not equal to "(" or ")",
It can be written as AB 
(A concatenated with B), 
where A and B are VPS's, or
It can be written as (A), 
where A is a VPS.

We can similarly define the nesting depth 
depth(S) of any VPS S as follows:
depth("") = 0
depth(C) = 0, where C is a string with a single character not equal to "(" or ")".
depth(A + B) = max(depth(A), depth(B)), where A and B are VPS's.
depth("(" + A + ")") = 1 + depth(A), where A is a VPS.
For example, "", "()()", and "()(()())" are VPS's (with nesting depths 0, 1, and 2), and ")(" and "(()" are not VPS's.

Given a VPS represented as string s, return the nesting depth of s.
*/

// beats 100% LC users
int maxDepth(string s) {
    int depth = 0;
    stack<char> st;
    for (auto &ch : s) {
        if (ch == '(') {
            st.push(ch);
            depth = max(depth, (int)st.size());
        }
        else if (ch == ')')
            st.pop();
    }
    return depth;
}

int main() {

  string s_1 = "{[(])}";
  bool expected_1 = false;
  bool output_1 = isBalanced(s_1);
  check(expected_1, output_1);

  string s_2 = "{{[[(())]]}}";
  bool expected_2 = true;
  bool output_2 = isBalanced(s_2);
  check(expected_2, output_2);

  string s_3 = "{}()";
  bool expected_3 = true;
  bool output_3 = isBalanced(s_3);
  check(expected_3, output_3);
  
  string s = "(()"; cout << longestValidParentheses(s) << endl;
  cout << "Minimum add to make valid string: " << minAddToMakeValidOptimized("(()") << endl;

  s = "lee(t(c)o)de)";
  cout << "Min removed to make valid string: " << s << " -> " << minRemoveToMakeValidOptimized(s) << endl;
  return 0;
  
}
