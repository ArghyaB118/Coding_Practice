/* LC#76

Given two strings s and t 
of lengths m and n respectively, 
return the minimum window substring
of s such that every character in t 
(including duplicates) 
is included in the window. 
If there is no such substring, 
return the empty string "".

The testcases will be generated 
such that the answer is unique.
*/

bool matchMap(unordered_map<char, int>& tmp_counts, 
	unordered_map<char, int>& counts) {
	for (auto &i : counts) {
		if (tmp_counts.find(i.first) == tmp_counts.end())
			return false;
		else if (i.second > tmp_counts[i.first])
			return false;
	}
	return true;
}

string minWindow(string s, string t) {
	unordered_map<char, int> counts;
	for (auto &ch : t) {
		if (counts.find(ch) == counts.end())
			counts[ch] = 1;
		else
			counts[ch]++;
	}
    for (auto &i : counts)
        cout << i.first << " " << i.second << endl;

	string res = "";
	for (int i = 0; i < s.length(); i++) {
		if (counts.find(s[i]) != counts.end()) {
			int j = i;
			unordered_map<char, int> tmp_counts;
			while (j < s.length()) {
                cout << i << " " << j << endl;
				if (counts.find(s[j]) != counts.end() 
					&& tmp_counts.find(s[j]) != tmp_counts.end())
					tmp_counts[s[j]]++;
				else if (counts.find(s[j]) != counts.end() 
					&& tmp_counts.find(s[j]) == tmp_counts.end())
					tmp_counts[s[j]] = 1;
				
				if (matchMap(tmp_counts, counts) && res == "") {
					res = s.substr(i, j - i + 1);
					break;
				}
				else if (matchMap(tmp_counts, counts) 
					&& res != ""
					&& res.length() > j - i + 1) {
					res = s.substr(i, j - i + 1);
					break;
				}

                j++;
			}
		}
	}
	return res;
}