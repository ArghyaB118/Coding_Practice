/* LC#1047

You are given a string s consisting 
of lowercase English letters. 
A duplicate removal consists of 
choosing two adjacent and equal letters and removing them.

We repeatedly make duplicate removals 
on s until we no longer can.

Return the final string after 
all such duplicate removals have been made. 
It can be proven that the answer is unique.
*/

// "abbbabaaa" => "b"
string removeDuplicates(string s) {
    string t = "";
    char ignore;
    for (auto &ch : s) {
        if (t.empty())
            t.push_back(ch);
        else if (ch != t.back() && ch != ignore)
            t.push_back(ch);
        else if (ch == t.back())
            t.pop_back();
        ignore = ch;
    }
    return t;
}

// beats ~85% LC users
// "abbbabaaa" => "ababa"
string removeDuplicates(string s) {
    string t = "";
    for (auto &ch : s) {
        if (t.empty())
            t.push_back(ch);
        else if (ch != t.back())
            t.push_back(ch);
        else if (ch == t.back())
            t.pop_back();
    }
    return t;
}