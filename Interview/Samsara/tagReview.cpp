/*
Given an array of reviews,
a set of positive words,
a set of negative words,
and a set of intensifiers,
mark each review as "positive"
"negative" or "neutral".

positive word does +1 to impact.
negative word does -1 to impact.
intensifier does +1 or -1 to the next
positive or negative word.
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

vector<string> solution(vector<string> reviews, 
vector<string> positiveWords, 
vector<string> negativeWords, 
vector<string> intensifiers) {
    unordered_set<string> pw, nw, iw;
    for (auto &s : positiveWords)
        pw.insert(s);
    for (auto &s : negativeWords)
        nw.insert(s);
    for (auto &s : intensifiers)
        iw.insert(s); 
    vector<string> result;
    for (auto &r : reviews) {
        string tmp = "";
        int impact = 0, intense = 0;
        for (auto &ch : r) {
            if (ch != ' ')
                tmp.push_back(ch);
            else if (pw.find(tmp) != pw.end()) {
                impact += (intense + 1);
                intense = 0;
            }
            else if (nw.find(tmp) != nw.end()) {
                impact -= (intense + 1);
                intense = 0;
            }
            else if (iw.find(tmp) != iw.end()) {
                intense++;
            }
            
            if (ch == ' ')
                tmp = "";
        }
        cout << tmp << endl;
        if (tmp != "") {
            if (pw.find(tmp) != pw.end())
                impact += intense + 1;
            else if (nw.find(tmp) != nw.end())
                impact -= intense + 1;
        }
        
        cout << impact << endl;
        if (impact == 0)
            result.push_back("neutral");
        else if (impact > 0)
            result.push_back("positive");
        else if (impact < 0)
            result.push_back("negative");
    }
    return result;
}

int main () {
    vector<string> positiveWords = {"good", "well"};
    vector<string> negativeWords = {"bad", "worse", "worst"};
    vector<string> intensifiers = {"very"};
    vector<string> reviews = 
    {"very bad bro", "he is very well", 
        "he is a very very good boy"};
    vector<string> tone = solution(reviews, positiveWords, negativeWords, intensifiers);
    for (auto &s : tone)
        cout << s << endl;
    return -1;
}