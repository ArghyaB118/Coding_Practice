/* LC#791
 
 You are given two strings order and s. 
 All the characters of order are unique 
 and were sorted in some custom order previously.
 
 Permute the characters of s so that 
 they match the order that order was sorted. 
 More specifically, if a character x occurs before 
 a character y in order, 
 then x should occur before y in the permuted string.

 Return any permutation of s that satisfies this property.
 
 Input: order = "cba", s = "abcd"
 Output: "cbad"
 Explanation:
 "a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a".
 Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.*/

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// beats ~50% LC users
string customSortString (string order, string s) {
    unordered_map<char, int> hashmap;
    for (int i = 0; i < s.length(); i++) {
        if (hashmap.find(s[i]) != hashmap.end())
            hashmap[s[i]]++;
        else
            hashmap[s[i]] = 1;
    }
    string t = "";
    for (int i = 0; i < order.length(); i++) {
        if (hashmap.find(order[i]) != hashmap.end()) {
            for (int j = 0; j < hashmap[order[i]]; j++)
                t.push_back(order[i]);
            hashmap.erase(order[i]);
        }
    }
    for (auto i : hashmap) {
        for (int j = 0; j < i.second; j++)
            t.push_back(i.first);
    }
    return t;
}

// beats 53% LC users
string customSortString2 (string order, string s) {
    unordered_map<char, int> counts;
    for (auto& i : order)
        counts[i] = 0;
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if (counts.find(s[i]) != counts.end())
            counts[s[i]]++;
        else {
            result.push_back(s[i]);
        }
    }
    for (auto& i : order) {
        for (int j = 0; j < counts[i]; j++)
            result.push_back(i);
    }
    return result;
}

int main () {
	string order = "cba", s = "abcd";
	string result = customSortString2 (order, s);
	cout << result << endl;
	return 0;
}
