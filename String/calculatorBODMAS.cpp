/* LC#227

Basic Calculator II

Given a string s which represents an expression, 
evaluate this expression and return its value. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. 
All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which 
evaluates strings as mathematical expressions, such as eval().

Input: s = "3+2*2"
Output: 7

Input: s = " 3/2 "
Output: 1

Input: s = " 3+5 / 2 "
Output: 5

s consists of integers and operators ('+', '-', '*', '/') 
separated by some number of spaces.
s represents a valid expression.
The answer is guaranteed to fit in a 32-bit integer.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

string removeSpaces (string s) {
	string t;
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]) || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			t.push_back(s[i]);
		}
	}
	return t;
}

int operations (vector<string> v) {
	int size = v.size();
	while (size > 1) {
		for (int i = 0; i < v.size(); i++) {
			if (v[i] == "/") {
				int num = stoi(v[i - 1]) / stoi(v[i + 1]);
				v[i] = to_string(num);
				v.erase(v.begin() + i + 1);
				v.erase(v.begin() + i - 1);
			}
		}
		size = 1;
	}
	for (string & sv : v)
		cout << sv;
	cout << endl;
	return 0;
}


vector<string> split (string s) {
	string tmp;
	vector<string> v;
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]))
			tmp.push_back(s[i]);
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			v.push_back(tmp); tmp.clear(); 
			tmp.push_back(s[i]); v.push_back(tmp); tmp.clear();
		}
	}
	v.push_back(tmp);
	return v;
}

int calculate (string s) {
	s = removeSpaces(s);
	vector<string> v = split(s);
	for (string & sv : v)
		cout << sv;
	cout << endl;
	operations(v);
/*	vector<string> v = operations(s);
	while (v.size() > 1) {
		for (int i = 0; i < v.size(); i++)
			if (s[i] == '/') {
				int num = stoi(s[i - 1]) / stoi(s[i + 1]);
				v.erase(v.begin() + )
			}
	}*/
	return 0;
}

vector<string> processDM (vector<string> &s) {
	vector<string> ss;
	for (int i = 0; i < s.size(); i++) {
		// cout << i << endl;
		if (s[i] != "/" && s[i] != "*")
			ss.push_back(s[i]);
		else {
			if (s[i] == "/")
				ss.back() = to_string(stoi(ss.back()) / stoi(s[i + 1]));
			else if (s[i] == "*")
				ss.back() = to_string(stoi(ss.back()) * stoi(s[i + 1]));
			i += 1;
		}
	}
	return ss;
}

vector<string> processAS (vector<string> &s) {
	vector<string> ss;
	for (int i = 0; i < s.size(); i++) {
		// cout << i << endl;
		if (s[i] != "+" && s[i] != "-")
			ss.push_back(s[i]);
		else {
			if (s[i] == "+")
				ss.back() = to_string(stoi(ss.back()) + stoi(s[i + 1]));
			else if (s[i] == "-")
				ss.back() = to_string(stoi(ss.back()) - stoi(s[i + 1]));
			i += 1;
		}
	}
	return ss;
}

int calculateCondensed (string s) {
	int i = 0, n = s.length();
	string tmp;
	vector<string> ss;
	while (i < n) {
		if (isdigit(s[i]))
			tmp += s[i];
		else {
			if (tmp != "")
				ss.push_back(tmp);
			tmp.clear();
			if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
				tmp += s[i];
				ss.push_back(tmp);
				tmp.clear();
			}
		}
		i++;
	}
	if (tmp != "")
		ss.push_back(tmp);

	/*for (auto &i : ss)
		cout << i << " ";
	cout << endl;*/
	ss = processDM(ss);
	/*for (auto &i : ss)
		cout << i << " ";
	cout << endl;*/
	ss = processAS(ss);	
	/*for (auto &i : ss)
		cout << i << " ";
	cout << endl;*/
	return stoi(ss[0]);
}


/* LC#29

Given two integers dividend and divisor, 
divide two integers without using 
multiplication, division, and mod operator.

The integer division should truncate toward zero, 
which means losing its fractional part. 
For example, 8.345 would be truncated to 8, 
and -2.7335 would be truncated to -2.

Return the quotient after dividing dividend by divisor.

Note: Assume we are dealing with an environment 
that could only store integers 
within the 32-bit signed integer range: [−2^31, 2^31 − 1]. 
For this problem, if the quotient is 
strictly greater than 2^31 - 1, 
then return 231 - 1, 
and if the quotient is strictly less than -2^31, 
then return -2^31.
*/

int divide(int dividend, int divisor) {
	if (dividend == 0)
		return 0;
	if (dividend < 0 && divisor < 0)
		return divide ((-1) * dividend, (-1) * divisor);
	if (dividend < 0 && divisor > 0)
		return (-1) * divide ((-1) * dividend, divisor);
	if (dividend > 0 && divisor < 0)
		return (-1) * divide (dividend, (-1) * divisor);
	if (divisor == 1)
		return dividend;

	int tmp = 0, count = 0;
	while (tmp + divisor <= dividend) {
		tmp += divisor;
		count++;
	}
	return count;
}

int main () {
	string s = "1+2*5/3+6/4*2"; //"1-1+1"; //"1+1+1"; //"3+5 / 2 ";
	cout << calculateCondensed(s) << endl;
	return 0;
}