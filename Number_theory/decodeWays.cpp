/* LC#91

A message containing letters from A-Z 
can be encoded into numbers using the following mapping:

To decode an encoded message, 
all the digits must be grouped 
then mapped back into letters 
using the reverse of the mapping above 
(there may be multiple ways). 
For example, "11106" can be mapped into:
"AAJF" with the grouping (1 1 10 6)
"KJF" with the grouping (11 10 6)

Given a string s containing only digits, 
return the number of ways to decode it.
The test cases are generated so that 
the answer fits in a 32-bit integer.
*/

int numDecodings(string s) {
	if (s[0] == '0')
		return 0;
	else if (s.length() == 1)
		return 1;
	vector<int> dp(s.length(), 0);
	dp[0] = 1;
	if (s[1] == '0')
		dp[1] = 1;
	else {
		int num = stoi(s.substr(0, 2));
		if (num <= 26)
			dp[1] = 2;
		else
			dp[1] = 1;
	}
	if (s.length() == 2)
		return dp[1];
	for (int i = 2; i < s.length(); i++) {
		if (s[i] == '0' && (s[i - 1] != '1' && s[i - 1] != '2'))
			return 0;
		else if (s[i] == '0' && (s[i - 1] == '1' || s[i - 1] == '2'))
			dp[i] = dp[i - 1];
		else if (s[i] != '0')
			dp[i] = dp[i - 1] + dp[i - 2];
	}
	return dp[s.length() - 1];
}

int numDecodingsOld(string s) {
  vector<int> encrypted;
  for (int i = 0; i < s.length(); i++) {
    encrypted.push_back(int(s[i]) - 64);
  }
  int dp[encrypted.size()];
  dp[0] = (encrypted[0] > 10) ? 2 : 1;
  if (encrypted.size() == 1)
    return dp[0];
  else {
    for (int i = 1; i < encrypted.size(); i++) {
      if (encrypted[i] <= 10)
        dp[i] = dp[i - 1];
      else {
        if (encrypted[i - 1] < 10)
          dp[i] = dp[i - 1] + 2;
        else if (encrypted[i - 1] == 10)
          dp[i] = dp[i - 1] + 1;
        else
          dp[i] = dp[i - 1] + 2;
      }
    }
  }  
  return dp[encrypted.size() - 1];
}
/* LC#2060

An original string, consisting of lowercase English letters, 
can be encoded by the following steps:

Arbitrarily split it into a sequence 
of some number of non-empty substrings.
Arbitrarily choose some elements (possibly none) of the sequence, 
and replace each with its length (as a numeric string).

Concatenate the sequence as the encoded string.
For example, one way to encode an original string 
"abcdefghijklmnop" might be:

Split it as a sequence: ["ab", "cdefghijklmn", "o", "p"].
Choose the second and third elements 
to be replaced by their lengths, respectively. 
The sequence becomes ["ab", "12", "1", "p"].
Concatenate the elements of the sequence 
to get the encoded string: "ab121p".
Given two encoded strings s1 and s2, 
consisting of lowercase English letters 
and digits 1-9 (inclusive), 
return true if there exists an original string 
that could be encoded as both s1 and s2. 
Otherwise, return false.

Note: The test cases are generated 
such that the number of consecutive digits 
in s1 and s2 does not exceed 3.
*/

vector<string> possibleEncryptions (string s) {
	vector<string> res;
	bool number_mode = false;
	string tmp = "";
	for (int i = 0, i < s.length(); i++) {
		if (number_mode && isdigit(s[i]))
			tmp += s[i];
		else if (!number_mode && isalpha(s[i]))
			tmp += s[i];
		else if (number_mode && isalpha(s[i])) {
			res.push_back(tmp);
			tmp.clear();
		}
		else if (!number_mode && isdigit(s[i])) {
			res.push_back(tmp);
			tmp.clear();
		}
	}
	if (tmp != "")
		res.push_back(tmp);
	return res;
}

int totalLength (vector<string>& ss) {
	int l = 0;
	for (auto &s : ss) {
		if (isalpha(s[0]))
			l += s.length();
		else
			l += stoi(s);
	}
	return l;
}

bool possiblyEquals (string s1, string s2) {
	vector<string> ss1 = possibleEncryptions(s1);
	vector<string> ss2 = possibleEncryptions(s2);
	if (totalLength(ss1) != totalLength(ss2))
		return false;
	int l1 = 0, l2 = 0, i = 0, j = 0;
	return true;
}