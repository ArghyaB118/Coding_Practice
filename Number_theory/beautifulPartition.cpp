/* LC#2478
 
 You are given a string s that consists of the digits '1' to '9' and two integers k and minLength.
 
 A partition of s is called beautiful if:

 s is partitioned into k non-intersecting substrings.
 Each substring has a length of at least minLength.
 Each substring starts with a prime digit and ends with a non-prime digit. Prime digits are '2', '3', '5', and '7', and the rest of the digits are non-prime.
 Return the number of beautiful partitions of s. Since the answer may be very large, return it modulo 109 + 7.

 A substring is a contiguous sequence of characters within a string.

 Input: s = "23542185131", k = 3, minLength = 2
 Output: 3
 Explanation: There exists three ways to create a beautiful partition:
 "2354 | 218 | 5131"
 "2354 | 21851 | 31"
 "2354218 | 51 | 31"
 
 Input: s = "23542185131", k = 3, minLength = 3
 Output: 1
 Explanation: There exists one way to create a beautiful partition: "2354 | 218 | 5131"
 
 nput: s = "3312958", k = 3, minLength = 1
 Output: 1
 Explanation: There exists one way to create a beautiful partition: "331 | 29 | 58"
 
 Constraints:

 1 <= k, minLength <= s.length <= 1000
 s consists of the digits '1' to '9'.*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> Pair;

bool isPrime (char ch) {
    if (ch == '2' || ch == '3' || ch == '5' || ch == '7')
        return true;
    return false;
}

int beautifulPartitions(string s, int k, int minLength) {
    int length = s.length();
    if (!isPrime(s[0]) || isPrime(s[length - 1]) || minLength > s.length())
        return 0;
    if (k == 1)
        return 1;
    
    int count = 0, left = 0;
    
    queue<Pair> q;
    for (int i = 0; i < length - 1; i++)
        if (i >= minLength - 1 && !isPrime(s[i]) && isPrime(s[i + 1]))
            q.push({i, 1});
        
    while (!q.empty()) {
        Pair tmp = q.front(); q.pop();
        cout << tmp.first << " " << tmp.second << endl;
        if (tmp.second == k - 1) {
            if (tmp.first < length - 1 && isPrime(s[tmp.first + 1]) && length - 1 - tmp.first >= minLength)
                count++;
        }
        else {
            for (int i = tmp.first + 1; i < length - 1; i++) {
                if (i >= minLength + tmp.first && !isPrime(s[i]) && isPrime(s[i + 1]))
                    q.push({i, tmp.second + 1});
            }
        }
    }
    return count;
}

int main () {
    string s = "38737664528187667419688711491264689456727783517411923972227428986913355726499196714767766496823989939585234733115996197583248799596843464726921";
    int k = 36, minLength = 1;
    // string s = "783938233588472343879134266968"; // 783938 2335884 7234 3879134266968
    // int k = 4, minLength = 6;
    // string s = "23542185131";
    // int k = 3, minLength = 3;
    cout << beautifulPartitions(s, k, minLength) << endl;
    return 0;
}
