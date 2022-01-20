/*
A valid number can be split up into these components (in order):

A decimal number or an integer.
(Optional) An 'e' or 'E', followed by an integer.
A decimal number can be split up into these components (in order):

(Optional) A sign character (either '+' or '-').
One of the following formats:
One or more digits, followed by a dot '.'.
One or more digits, followed by a dot '.', followed by one or more digits.
A dot '.', followed by one or more digits.
An integer can be split up into these components (in order):

(Optional) A sign character (either '+' or '-').
One or more digits.
For example, all the following are valid numbers: 
["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"], 
while the following are not valid numbers: ["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"].
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isInteger (string s) {
	if (s[0] == '+' || s[0] == '-') {
		if (s.length() == 1)
			return false;
		for (int i = 1; i < s.length(); i++)
			if (int(s[i]) < 48 || int(s[i]) > 57)
				return false;
		return true;	
	}
	for (int i = 0; i < s.length(); i++)
		if (int(s[i]) < 48 || int(s[i]) > 57)
			return false;
	return true;
}

bool isDecimal (string s) {
	return true;
}

bool invalidChar (string s) {
	for (int i = 0; i < s.length(); i++)
		if (int(s[i]) < 48 || int(s[i]) > 57)
			if (s[i] != '+' && s[i] != '-')
				if (s[i] != '.' && s[i] != 'e' && s[i] != 'E')
					return true;
	return false;
}

bool validNumber (string s) {
	if (invalidChar(s))
		return false;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == 'e' || s[i] == 'E') {
			if (i == 0 || i == s.length() - 1)
				return false;
			return isDecimal(s.substr(0, i)) && isInteger(s.substr(i+1, s.length()));
		}
	}
	return isDecimal(s);
}


int main () {
	vector<string> nums{"2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"};
	nums.insert(nums.end(), {"abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"});
	for (string & s : nums)
		cout << boolalpha << validNumber(s) << endl;
	return 0;
}