/* LC#1055
 
 A subsequence of a string is a new string 
 that is formed from the original string 
 by deleting some (can be none) of the characters 
 without disturbing the relative positions 
 of the remaining characters. 
 (i.e., "ace" is a subsequence 
 of "abcde" while "aec" is not).
 
 Given two strings source and target, 
 return the minimum number of subsequences 
 of source such that their concatenation equals target. 
 If the task is impossible, return -1.
 
 Input: source = "abc", target = "abcbc"
 Output: 2
 Explanation: The target "abcbc" can be formed by "abc" and "bc", 
 which are subsequences of source "abc".
 
 Input: source = "abc", target = "acdbc"
 Output: -1
 Explanation: The target string cannot be constructed 
 from the subsequences of source string 
 due to the character "d" in target string.
 
 Input: source = "xyz", target = "xzyxz"
 Output: 3
 Explanation: The target string can be constructed 
 as follows "xz" + "y" + "xz".
 */

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// O (m * n)
int shortestWay (string source, string target) {
    int i = 0, j = 0, num = 0, length = 0;
    
    while (j < target.length()) {
        // cout << j << " " << num << endl;
        i = 0;
        length = 0;
        for (int i = 0; i < source.length(); i++) {
            if (source[i] == target[j]) {
                cout << i << " " << j << endl;
                j++; length++;
            }
        }
        if (length == 0)
            return -1;
        else
            num++;
    }
    return num;
}

/* Are all the letters in the source unique?
 The use an unordered_map to store the chars and the index. Do constant time lookup instead of
    1. linear time lookups like the algorithm with two pointers
    2. log m time lookup like the algorithm with map
*/
int shortestWayOpt (string source, string target) {
    int i = 0, j = 0, num = 0, length = 0;
    unordered_map<char, int> um;
    for (int i = 0; i < source.length(); i++) {
        um.insert({source[i], i});
    }
    while (j < target.length()) {
        if (um.find(target[j]) == um.end())
            return -1;
        int tmp = um[target[j]], length = 0;
        for (int i = tmp; i < source.length(); i++) {
            if (source[i] == target[j]) {
                j++; length++;
            }
        }
        num++;
    }
    return num;
}

/* LC#1768

You are given two strings word1 and word2. 
Merge the strings by adding letters in alternating order, 
starting with word1. 
If a string is longer than the other, 
append the additional letters 
onto the end of the merged string.

Return the merged string.
*/

// beats 100% LC users
string mergeAlternately(string word1, string word2) {
    string result = "";
    int m = word1.length(), n = word2.length();
    int i = 0, j = 0;
    while (i < m && j < n) {
        result.push_back(word1[i]);
        result.push_back(word2[j]);
        i++; j++;
    }
    while (i < m) {
        result.push_back(word1[i]); i++;
    }
    while (j < n) {
        result.push_back(word2[j]); j++;
    }
    return result;
}

int main () {
    string source = "abc", target = "abcbc";
    cout << shortestWayOpt (source, target) << endl;
    return 0;
}
