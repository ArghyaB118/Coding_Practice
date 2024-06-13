/*
Encrypted Words

You've devised a simple encryption method for alphabetic strings that shuffles the characters in such a way that the resulting string is hard to quickly read, but is easy to convert back into the original string.
When you encrypt a string S, you start with an initially-empty resulting string R and append characters to it as follows:
Append the middle character of S (if S has even length, then we define the middle character as the left-most of the two central characters)
Append the encrypted version of the substring of S that's to the left of the middle character (if non-empty)
Append the encrypted version of the substring of S that's to the right of the middle character (if non-empty)
For example, to encrypt the string "abc", we first take "b", and then append the encrypted version of "a" (which is just "a") and the encrypted version of "c" (which is just "c") to get "bac".
If we encrypt "abcxcba" we'll get "xbacbca". That is, we take "x" and then append the encrypted version "abc" and then append the encrypted version of "cba".
*/

#include <iostream>
#include <string>
#include <vector>
// Add any extra import statements you may need here

using namespace std;

// Add any helper functions you may need here
string encryptionRecur(string s, string c) {
//  cout << s << " " << c << endl;
  if (s.length() == 0)
    return c;
  else if (s.length() == 1) {
    c.push_back(s[0]);
    return c;
  }
  else if (s.length() == 2) {
    c.push_back(s[0]);
    c = encryptionRecur(s.substr(1,1), c);
    return c;
  }
  else if (s.length() > 2 && s.length() % 2 == 0) {
    c.push_back(s[s.length() / 2 - 1]);
    c = encryptionRecur(s.substr(0, s.length() / 2 - 1),c);
    c = encryptionRecur(s.substr(s.length() / 2, s.length()),c);
    return c;
  }
  else if (s.length() > 1 && s.length() % 2 != 0) {
    c.push_back(s[s.length() / 2]);
    c = encryptionRecur(s.substr(0, s.length() / 2),c);
    c = encryptionRecur(s.substr(s.length() / 2 + 1, s.length()),c);
    return c;
  }
  return c;
}

string findEncryptedWord(string s) {
  // Write your code here
  string c; 
  c = encryptionRecur(s, c);
  return c;
}

// KJF -> 11 10 6 -> 2 


// These are the tests we use to determine if the solution is correct.
// You can add your own at the bottom.

void printString(string& str) {
  cout << "[\"" << str << "\"]";
}

int test_case_number = 1;

void check(string& expected, string& output) {
  bool result = (expected == output);
  const char* rightTick = u8"\u2713";
  const char* wrongTick = u8"\u2717";
  if (result) {
    cout << rightTick << " Test #" << test_case_number << "\n";
  }
  else {
    cout << wrongTick << " Test #" << test_case_number << ": Expected ";
    printString(expected); 
    cout << " Your output: ";
    printString(output);
    cout << endl; 
  }
  test_case_number++;
}


/* LC#953

In an alien language, surprisingly, 
they also use English lowercase letters, 
but possibly in a different order. 
The order of the alphabet is 
some permutation of lowercase letters.

Given a sequence of words written 
in the alien language, 
and the order of the alphabet, 
return true if and only if 
the given words are sorted lexicographically 
in this alien language.
*/

// beats ~25% LC users
bool check_order (string word1, string word2, unordered_map<char, int>& char_order) {
  for (int i = 0; i < min(word1.length(), word2.length()); i++) {
    if (char_order[word1[i]] < char_order[word2[i]])
      return true;
    else if (char_order[word1[i]] > char_order[word2[i]])
      return false;
  }
  if (word1.length() > word2.length())
    return false;
  return true;
}

bool isAlienSorted(vector<string>& words, string order) {
  unordered_map<char, int> char_order;
  int i = 0;
  for (auto &ch : order) {
    char_order[ch] = i; i++;
  }
  if (words.size() == 0 || words.size() == 1)
    return true;

  for (int i = 1; i < words.size(); i++) {
    if (!check_order(words[i], words[i - 1], char_order))
      return false;
  }

  return true;
}

int main() {

  string s_1 = "abc";
  string expected_1 = "bac";
  string output_1 = findEncryptedWord(s_1);
  check(expected_1, output_1);

  string s_2 = "abcd";
  string expected_2 = "bacd";
  string output_2 = findEncryptedWord(s_2);
  check(expected_2, output_2);

  // Add your own test cases here
  cout << numDecodings("KJF") << endl;
}