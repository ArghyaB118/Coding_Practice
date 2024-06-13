/* LC#125

A phrase is a palindrome if, 
after converting all uppercase letters into lowercase letters 
and removing all non-alphanumeric characters, 
it reads the same forward and backward. 
Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, 
or false otherwise.

Input: s = "A man, a plan, a canal: Panama"
Output: true
*/

#include <iostream>
#include <string>
#include <stack>
using namespace std;

// use two pointers
// beats 100% LC users
bool isPalindrome(string s) {
	int left = 0, right = s.length() - 1;
	while (left < right) {
		if (!isalnum(s[left]))
			left++;
		else if (!isalnum(s[right]))
			right--;
		else if (tolower(s[left]) != tolower(s[right]))
			return false;
		else if (tolower(s[left]) == tolower(s[right])) {
			left++; right--;
		}
	}
	return true;
}

// push back in a new string
bool isPalindrome1(string s) {
    string t;
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (s[i] != '\n' && s[i] != ' ' && ispunct(s[i]) == false)
            t.push_back(tolower(s[i]));
    }
    for (int i = 0; i < t.length() / 2; i++)
        if (t[i] != t[t.length() - i - 1])
            return false;
    return true;
}

// modify the same string
bool isPalindromeInPlace (string s) {
    s.erase(remove(s.begin(), s.end(), '\n'), s.end());
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    for (int i = 0, len = s.length(); i < len; i++) {
        if (ispunct(s[i])) {
            s.erase(i--,1); len = s.length();
        }
    }
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);
    cout << s;
    for (int i = 0; i < s.length() / 2; i++)
        if (s[i] != s[s.length() - i - 1])
            return false;
    return true;
}

string removeNonAlphaNumerics(string s) {
	string s1;
	for (int i = 0; i < s.length(); i++) {
		if (int(s[i]) >= 97 && int(s[i]) <= 122)
			s1.push_back(s[i]);
		else if (int(s[i]) >= 65 && int(s[i]) <= 90)
			s1.push_back(char(int(s[i]) + 32));
		else if (int(s[i]) >= 48 && int(s[i]) <= 57)
			s1.push_back(s[i]);
	}
	return s1; 
}

bool isPalindrome2 (string s) {
	if (s.length() == 0 || s.length() == 1)
		return true;
	stack<char> s1;
	for (int i = 0; i < s.length(); i++)
		s1.push(char(s[i]));
	for (int i = 0; i < s.length(); i++) {
		char ch = s1.top(); s1.pop();
		if (ch != s[i])
			return false;
	}
	return true;
}

/* LC#5

Given a string s, return the longest 
palindromic substring in s.
*/

bool isPalindrome3 (string &s, int i, int j) {
	while (i < j) {
		if (s[i] != s[j])
			return false;
		i++; j--;
	}
	return true;
}

int longestPalindrome1(string s) {
	if (s == "")
		return 0;
	int length = 1;
	for (int i = 0; i < s.length(); i++) {
		if (s.length() - i < length)
			return length;
		int j = s.length() - 1;
		while (i < j) {
			if (isPalindrome3(s, i, j)) {
				length = max(length, j - i + 1);
				break;
			}
			else
				j--;
		}
	}
	return length;
}

// memory limit exceeded
string longestPalindrome2(string s) {
	if (s == "")
		return s;
	string ans = ""; ans.push_back(s[0]);
	for (int i = 0; i < s.length(); i++) {
		if (s.length() - i < ans.length())
			return ans;
		int j = s.length() - 1;
		while (i < j) {
			if (isPalindrome3(s, i, j) && j - i + 1 > ans.length()) {
				ans = s.substr(i, j - i + 1);
				break;
			}
			else
				j--;
		}
	}
	return ans;
}

// beats ~43% LC users
// O(n ^ 3)
string longestPalindrome3(string s) {
	if (s == "")
		return s;
	int left = 0, right = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s.length() - i < right - left + 1)
			return s.substr(left, right - left + 1);
		int j = s.length() - 1;
		while (i < j) {
			if (isPalindrome3(s, i, j) && j - i + 1 > right - left + 1) {
				left = i; right = j;
				break;
			}
			else
				j--;
		}
	}
	return s.substr(left, right - left + 1);
}

// beats ~82% LC users
string longestPalindrome(string s) {
	if (s == "")
		return s;
	int left = 0, right = 0, n = s.length();
	for (int i = 0; i < n; i++) {
		int centre = i, x = 0;
		while (centre - x - 1 >= 0 
			&& centre + x + 1 < n 
			&& s[centre - x - 1] == s[centre + x + 1]) {
			x++;
		}
		if (right - left + 1 < 2 * x + 1) {
			left = centre - x;
			right = centre + x;
		}
	}
	for (int i = 0; i < n - 1; i++) {
		if (s[i] == s[i + 1]) {
			int l = i, r = i + 1, x = 0;
			while (l - x - 1 >= 0 
				&& r + x + 1 < n 
				&& s[l - x - 1] == s[r + x + 1]) {
				x++;
			}
			if (right - left + 1 < 2 * x + 2) {
				left = l - x;
				right = r + x;
			}
		}
	}
	return s.substr(left, right - left + 1);
}

// dp[i][j] = (dp[i + 1][j - 1]) && (is s[i] == s[j])
// Anything between two same letters is palindromic or not
//   a b c b d
// a 1 0 0 0 0
// b   1 0 1 0
// c     1 0 0
// b       1 0
// d         1

int longestPalindromicSubstring (string s) {
	bool dp[s.length()][s.length()];
	int max_length = 1;
	for (int i = 0; i < s.length(); i++) {
		dp[i][i] = true;
		int j = 0;
		while (j < i) {
			dp[i][j] = false;
			j++;
		}
	}
	for (int i = s.length() - 2; i >= 0; i--) {
		for (int j = i + 1; j < s.length(); j++) {
			if (dp[i+1][j-1] == true && s[i] == s[j]) {
				dp[i][j] = true;
				if (j - i + 1 > max_length)
					max_length = j - i + 1;
			}
			else
				dp[i][j] = false;
		}
	}
	return max_length;
}


/* LC#680

Given a string s, return true if the s can be palindrome 
after deleting at most one character from it.
*/

bool useDeletion = false;
// Use two pointers
bool validPalindromeWithDeletion (string s) {
	int left = 0, right = s.length() - 1;
	while (left < right) {
		if (s[left] != s[right] && useDeletion == true)
			return false;
		else if (s[left] != s[right] && useDeletion == false) {
			useDeletion = true;
			if (left + 1 == right)
				return true;
			else if (s[left + 1] == s[right] && s[left] == s[right - 1])
				return (validPalindromeWithDeletion (s.substr(left, right - left)) || validPalindromeWithDeletion (s.substr(left + 1, right - left)));
			else if (s[left + 1] == s[right] && s[left] != s[right - 1])
				left++;
			else if (s[left] == s[right - 1] && s[left + 1] != s[right])
				right--;
		}
		else {
			left++; right--;
		}
	}
	return true;
}


// A much faster way is not to define a global boolean
// Instead have a root function and a utility funtion
// beats ~91% LC users
bool validPalindromeWithDeletionUtil (string s, bool useDelete, int left, int right) {
	while (left < right) {
		if (s[left] != s[right] && useDelete == true)
			return false;
		else if (s[left] != s[right] && useDelete == false) {
			useDelete = true;
			if (left + 1 == right)
				return true;
			else if (s[left + 1] == s[right] && s[left] == s[right - 1])
				return (validPalindromeWithDeletionUtil 
					(s, useDelete, left, right - 1) 
					|| validPalindromeWithDeletionUtil 
					(s, useDelete, left + 1, right));
			else if (s[left + 1] == s[right] 
				&& s[left] != s[right - 1])
				left++;
			else if (s[left] == s[right - 1] 
				&& s[left + 1] != s[right])
				right--;
		}
		else {
			left++; right--;
		}
	}
	return true;
}

bool validPalindromeWithDeletionRoot (string s) {
	if (s.length() == 0)
		return true;
	else if (s.length() == 1)
		return true;
	return validPalindromeWithDeletionUtil (s, false, 0, s.length() - 1);
}

/* LC#1216

Given a string s and an integer k, 
return true if s is a k-palindrome.

A string is k-palindrome 
if it can be transformed into a palindrome 
by removing at most k characters from it.
*/

// memory limit exceeded
bool isValidPalindrome(string s, int k) {
	if (k < 0)
		return false;
	int left = 0, right = s.length() - 1;
	while (left < right) {
		if (s[left] == s[right]) {
			left++; right--;
		}
		else if (s[left] != s[right]) {
			return isValidPalindrome(s.substr(left, right - left), k - 1)
				|| isValidPalindrome(s.substr(left + 1, right - left), k - 1);
		}
	}
	return true;
}

bool isValidPalindromeUtil(string &s, int left, int right, int k) {
	if (k < 0)
		return false;
	if (left == right)
		return true;
	while (left < right) {
		if (s[left] == s[right]) {
			left++; right--;
		}
		else if (s[left] != s[right]) {
			return isValidPalindromeUtil(s, left + 1, right, k - 1)
				|| isValidPalindromeUtil(s, left, right - 1, k - 1);
		}
	}
	return true;
}

bool isValidPalindrome(string s, int k) {
	return isValidPalindromeUtil(s, 0, s.length() - 1, k);
}

/* LC#266

Given a string s, 
return true if a permutation of the string could form a 
palindrome and false otherwise.
*/

// beats ~26% LC users
bool canPermutePalindrome(string s) {
	unordered_map<char, int> char_count;
	for (auto &ch : s) {
		char_count[ch]++;
	}
	bool used = false;
	for (auto &i : char_count) {
		if (!used && i.second == 1)
			used = true;
		else if (used && i.second == 1)
			return false;
	}
	return true;
}

// beats 100% LC users
bool canPermutePalindrome2(string s) {
	unordered_map<char, int> char_count;
	for (auto &ch : s) {
		char_count[ch]++;
	}
	int count = 0;
	for (auto &i : char_count) {
		if (i.second % 2 == 1)
			count++;
		if (count > 1)
            return false;
	}
	return true;
}

/* LC#234

Given the head of a singly linked list, 
return true if it is a palindrome
or false otherwise.

Follow up: Could you do it 
in O(n) time and O(1) space?
*/

// beats ~32% LC users
bool isPalindromeList (ListNode* head) {
	vector<int> v;
	while (head) {
		v.push_back(head->val);
		head = head->next;
	}
	int n = v.size();
	if (n == 1)
		return true;
	for (int i = 0; i < n / 2; i++) {
		if (v[i] != v[n - 1 - i])
			return false;
	}
	return true;
}

// O(1) space
bool isPalindrome (ListNode* head) {
	int count = 0;
    ListNode* tmp = head;
	while (tmp) {
		tmp = tmp->next;
		count++;
	}

    if (count == 1)
        return true;
    
    tmp = head;
	for (int i = 0; i < count / 2; i++) {
        cout << tmp->val << endl;
		tmp = tmp->next;
    }

	if (count % 2 == 1)
		tmp = tmp->next;

    cout << "here" << endl;
    ListNode* prev = NULL;
    ListNode* next = tmp->next;
	while (next != NULL) {
        cout << tmp->val << endl;
        ListNode* nxt = next->next;
        next->next = tmp;
        tmp->next = prev;
        tmp = next;
        next = nxt;
        prev = tmp;
	}

    cout << "here" << endl;
    cout << head->val << tmp->val << count / 2 << endl;

	for (int i = 0; i < count / 2; i++) {
        cout << head->val << tmp->val << endl;
		if (head->val != tmp->val)
			return false;
        head = head->next;
        tmp = tmp->next;
    }

	return true;
}

int main () {
	string s = "A man, a plan, a canal: Panama";
	s = removeNonAlphaNumerics(s);
	cout << "Is " << s << " a palindrome? " << boolalpha << isPalindrome(s) << endl;
	string s1 = "aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupuculmgmqfvnbgtapekouga";
	cout << "Is s1 a palindrome after deleting at most one char? " << validPalindromeWithDeletionRoot(s1) << endl;
	cout << "Length of longest palindromic substring of abcbd: " << longestPalindromicSubstring("abcbd") << endl; 
	
	cout << longestPalindrome("abacd") << endl;
	return 0;
}
