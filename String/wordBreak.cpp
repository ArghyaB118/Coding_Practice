/*
Given a string s and a dictionary of strings wordDict, return true 
if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


bool dictContains(string s, vector<string>& wordDict) {
	if (find(wordDict.begin(), wordDict.end(), s) != wordDict.end())
		return true;
	return false;
}

// ca -> false, cats -> true
// catsan -> false, catsand -> true
bool wordBreak(string s, vector<string>& wordDict) {
	if (s.size() == 0) { return false; }
	bool dp[s.size()]; memset(dp, false, sizeof(dp));
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (dp[j] && dictContains(s.substr(j+1, i))) {
				dp[i] = true; break;
			}
		}
	}
	return dp[s.length() - 1];        
}

/*
Given a string s and a dictionary of strings wordDict, 
add spaces in s to construct a sentence where each word 
is a valid dictionary word. Return all such possible sentences in any order.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]

Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []
*/

string wordBreakSpaceUtil (string s, map<char, int>, vector<string>& result) {
	if (s.length() == 0)
		return result;
	for (int i = 1; i <= s.length(); i++) {
		if (dict.find(s.substr(0, i)) != dict.end()) {
			result.push_back(result + "s.substr(0, i)" + " " + wordBreakSpaceUtil(i, s.length()));
		}
		else {
			return "";
		}
	}
}

vector<string> wordBreakSpace (string s, vector<string>& wordDict) {
	unordered_map<string, int> dict;
	for (int i = 0; i < wordDict.size(); i++)
		dict.insert({wordDict[i], 1});

	vector<string> result; 
	result.push_back(wordBreakSpaceUtil(s, dict, result));
}

int main () {
	string s = "applepenapple"; 
	vector<string> wordDict{"apple","pen"};
	cout << boolalpha << wordBreak(s, wordDict) << endl;
	return 0;
}