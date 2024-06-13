/* LC#38

The count-and-say sequence is a sequence 
of digit strings defined by the recursive formula:

countAndSay(1) = "1"
countAndSay(n) is the way you would "say" the digit string 
from countAndSay(n-1), 
which is then converted into a different digit string.

To determine how you "say" a digit string, 
split it into the minimal number of substrings 
such that each substring contains 
exactly one unique digit. 
Then for each substring, 
say the number of digits, 
then say the digit. 
Finally, concatenate every said digit.

For example, 
the saying and conversion for digit string 
"3322251" = 23321511

Explanation:
countAndSay(1) = "1"
countAndSay(2) = say "1" = one 1 = "11"
countAndSay(3) = say "11" = two 1's = "21"
countAndSay(4) = say "21" = one 2 + one 1 = "12" + "11" = "1211"
*/

// beats ~60% LC users
string one_step(string s) {
    stringstream ss;
    for (int i = 0; i < s.length(); i++) {
        char temp = s[i];
        int count = 1;
        while(i + 1 < s.length() && s[i + 1] == temp) {
            count++;
            i++;
        }
        ss << count << temp;
    }
    return ss.str();
}
string countAndSay(int n) {
    string x = "1";
    for(int i = 1; i < n; i ++) {
        x = one_step(x);
    }
    return x;
}