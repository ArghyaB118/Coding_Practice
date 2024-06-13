/* LC#249

We can shift a string by shifting 
each of its letters to its successive letter.

For example, "abc" can be shifted to be "bcd".
We can keep shifting the string to form a sequence.

For example, we can keep shifting "abc" 
to form the sequence: "abc" -> "bcd" -> ... -> "xyz".
Given an array of strings strings, 
group all strings[i] that belong 
to the same shifting sequence. 
You may return the answer in any order.

Input: strings = ["abc","bcd","acef","xyz","az","ba","a","z"]
Output: [["acef"],["a","z"],["abc","bcd","xyz"],["az","ba"]]
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;

bool isShifted(string& s, string& t) {
	// cout << "here " << s << t << endl;
	if (s.length() != t.length())
		return false;
	if (s == t)
        return true;
	int dist = (int)t[0] - (int)s[0];
	for (int i = 0; i < s.length(); i++) {
		int shifted = (int)s[i] + dist;
		if (shifted >= 97 && shifted <= 122)
			s[i] = static_cast<char>(shifted);
		else if (shifted < 97)
			s[i] = static_cast<char>(shifted + 26);
		else if (shifted > 122)
			s[i] = static_cast<char>(shifted - 26);
		if (s[i] != t[i])
			return false;
	}
	// cout << "here " << s << endl;
	if (s == t) 
		return true;
	return false;
}

vector<vector<string>> groupStrings(vector<string>& strings) {
	vector<bool> included (strings.size(), false);
	vector<vector<string>> result;
	for (int i = 0; i < strings.size(); i++) {
		if (included[i])
			continue;
		vector<string> tmp = {strings[i]};
		included[i] = true;
		for (int j = 0; j < strings.size(); j++) {
			if (j == i || included[j])
				continue;
			if (isShifted(strings[i], strings[j])) {
				tmp.push_back(strings[j]); 
				included[j] = true;
			}
		}
		result.push_back(tmp);
	}
	return result;
}

/* LC#721

Given a list of accounts 
where each element accounts[i] is a list of strings, 
where the first element accounts[i][0] is a name, 
and the rest of the elements 
are emails representing emails of the account.

Now, we would like to merge these accounts. 
Two accounts definitely belong to the same person 
if there is some common email to both accounts. 
Note that even if two accounts have the same name, 
they may belong to different people 
as people could have the same name. 
A person can have any number of accounts initially, 
but all of their accounts definitely have the same name.

After merging the accounts, 
return the accounts in the following format: 
the first element of each account is the name, 
and the rest of the elements 
are emails in sorted order. 
The accounts themselves can be returned in any order.
*/

string find (string s, 
	unordered_map<string, string>& parents) {
	if (parents[s] == s)
		return s;
	return find(parents[s], parents);
}

void combine (string s, string t, 
	unordered_map<string, string>& parents) {
	s = find(s, parents);
	t = find(t, parents);
	if (s == t)
		return;
	parents[t] = s;
}

set<string> dfs (string email, 
	unordered_map<string, string>& parents, 
	unordered_set<string>& visited) {
	set<string> emails;
	string parent = find(email, parents);

	for (auto &i : parents) {
		if (find(i.first, parents) == parent) {
			emails.insert(i.first);
			visited.insert(i.first);
		}
	}
	return emails;
}

vector<vector<string>> accountsMergeUnionFind 
(vector<vector<string>>& accounts) {
	unordered_map<string, string> parents;
	for (auto &account : accounts)
		for (int i = 1; i < account.size(); i++)
			parents[account[i]] = account[i];
	for (auto &account : accounts) {
		for (int i = 1; i < account.size(); i++) {
			combine (account[1], account[i], parents);
		}
	}
	unordered_set<string> visited;
	vector<vector<string>> result;
	for (auto &account : accounts) {
		if (visited.find(account[1]) == visited.end()) {
			string name = account[0];
			set<string> emails = dfs(account[1], parents, visited);
			vector<string> tmp;
			tmp.push_back(name);
			for (auto &email : emails)
				tmp.push_back(email);
			result.push_back(tmp);
		}
	}
    return result;
}

// Approach: Additional structure maintained
// vector of std::set of emails (as we needed sorted output)
// WRONG: we need bfs
typedef pair<string, unordered_set<string>> entry;

int isPresent (string e, vector<entry> entries) {
	if (entries.empty())
		return -1;
	for (int i = 0; i < entries.size(); i++) {
		if (entries[i].second.find(e) != entries[i].second.end())
			return i;
	}
	return -1;
}

vector<vector<string>> accountsMergeOld (vector<vector<string>>& accounts) {
	vector<entry> entries;
	for (auto &s : accounts) {
		string name = s[0];
		s.erase(s.begin());
		int index = -1;
		for (auto &e : s) {
			index = isPresent(e, entries);
			if (index >= 0) {
				break;
			}			
		}
		if (index >= 0) {
			for (auto &e : s) {
				entries[index].second.insert(e);
			}
		}
        else {
            entry e;
            e.first = name;
            for (auto &ss : s)
                e.second.insert(ss);
			entries.push_back(e);
		}
	}
	vector<vector<string>> result;
	for (auto &e : entries) {
		vector<string> s = {};
		s.push_back(e.first);
		for (auto &ee : e.second) {
			s.push_back(ee);
		}
		result.push_back(s);
	}
	return result;
}

// beats ~5% LC users
vector<vector<string>> accountsMerge (vector<vector<string>>& accounts) {
	vector<unordered_set<string>> email_accounts;
	int n = accounts.size();
	for (auto &account : accounts) {
		string name = account[0];
		unordered_set<string> emails;
		for (int i = 1; i < account.size(); i++) {
			emails.insert(account[i]);
		}
		email_accounts.push_back(emails);
	}

	vector<vector<string>> result;
	vector<bool> visited(accounts.size(), false);
	for (int i = 0; i < n; i++) {
		if (visited[i]) { continue; }
		vector<string> account = accounts[i];
		string name = account[0];
		set<string> emails;
		queue<string> q;
		for (int i = 1; i < account.size(); i++)
			q.push(account[i]);
		while (!q.empty()) {
			string email = q.front();
			q.pop();
			emails.insert(email);
			for (int i = 0; i < n; i++) {
				if (!visited[i] && email_accounts[i].find(email) != email_accounts[i].end()) {
					visited[i] = true;
					for (auto &e : email_accounts[i])
						q.push(e);
				}
			}
		}
		vector<string> tmp;
		tmp.push_back(name);
		for (auto &email : emails)
			tmp.push_back(email);
		result.push_back(tmp);
	}
	return result;
}

// beats ~5% LC users
vector<vector<string>> accountsMerge2 (vector<vector<string>>& accounts) {
	vector<unordered_set<string>> email_accounts;
	int n = accounts.size();
	for (auto &account : accounts) {
		string name = account[0];
		unordered_set<string> emails;
		for (int i = 1; i < account.size(); i++) {
			emails.insert(account[i]);
		}
		email_accounts.push_back(emails);
	}

	vector<vector<string>> result;
	vector<bool> visited(accounts.size(), false);
	for (int i = 0; i < n; i++) {
		if (visited[i]) { continue; }
		vector<string> account = accounts[i];
		string name = account[0];
		unordered_set<string> emails;
		queue<string> q;
		for (int i = 1; i < account.size(); i++)
			q.push(account[i]);
		while (!q.empty()) {
			string email = q.front();
			q.pop();
			emails.insert(email);
			for (int i = 0; i < n; i++) {
				if (!visited[i] && email_accounts[i].find(email) != email_accounts[i].end()) {
					visited[i] = true;
					for (auto &e : email_accounts[i])
						q.push(e);
				}
			}
		}
		vector<string> tmp;
		for (auto &email : emails)
			tmp.push_back(email);
        sort(tmp.begin(), tmp.end());
        tmp.insert(tmp.begin(), name);
		result.push_back(tmp);
	}
	return result;
}

// beats ~5% LC users
vector<vector<string>> accountsMerge3 (vector<vector<string>>& accounts) {
	int n = accounts.size();

	vector<vector<string>> result;
	vector<bool> visited(accounts.size(), false);
	for (int i = 0; i < n; i++) {
		if (visited[i]) { continue; }
		vector<string> account = accounts[i];
		string name = account[0];
		unordered_set<string> emails;
		queue<string> q;
		for (int i = 1; i < account.size(); i++)
			q.push(account[i]);
		while (!q.empty()) {
			string email = q.front();
			q.pop();
			emails.insert(email);
			for (int i = 0; i < n; i++) {
				if (!visited[i] && find(accounts[i].begin() + 1, accounts[i].end(), email) != accounts[i].end()) {
					visited[i] = true;
					for (int j = 1; j < accounts[i].size(); j++)
						q.push(accounts[i][j]);
				}
			}
		}
		vector<string> tmp;
		for (auto &email : emails)
			tmp.push_back(email);
        sort(tmp.begin(), tmp.end());
        tmp.insert(tmp.begin(), name);
		result.push_back(tmp);
	}
	return result;
}

int main () {
	vector<string> strings = 
	// {"fpbnsbrkbcyzdmmmoisaa","cpjtwqcdwbldwwrryuclcngw","a","fnuqwejouqzrif","js","qcpr","zghmdiaqmfelr","iedda","l","dgwlvcyubde","lpt","qzq","zkddvitlk","xbogegswmad","mkndeyrh","llofdjckor","lebzshcb","firomjjlidqpsdeqyn","dclpiqbypjpfafukqmjnjg","lbpabjpcmkyivbtgdwhzlxa","wmalmuanxvjtgmerohskwil","yxgkdlwtkekavapflheieb","oraxvssurmzybmnzhw","ohecvkfe","kknecibjnq","wuxnoibr","gkxpnpbfvjm","lwpphufxw","sbs","txb","ilbqahdzgij","i","zvuur","yfglchzpledkq","eqdf","nw","aiplrzejplumda","d","huoybvhibgqibbwwdzhqhslb","rbnzendwnoklpyyyauemm"};
	{"abc","bcd", "acef","xyz","az","ba","a","z","lpt","txb"};
	vector<vector<string>> result = groupStrings(strings);
	for (auto &i : result) {
		for (auto &j : i)
			cout << j << " ";
		cout << endl;
	}

	vector<vector<string>> accounts = 
	{{"Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"},
	{"Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"},
	{"Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"},
	{"Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"},
	{"Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"}};
	vector<vector<string>> merged_accounts = accountsMergeUnionFind (accounts);
	
	for (auto &i : merged_accounts)
		for (auto &j : i)
			cout << j << " ";
	return 0;
}