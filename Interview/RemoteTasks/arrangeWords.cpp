/*
arrange words in a sentence.
1. the words will come in ascending order 
    of length of words.
2. if two words are of same length,
    follow the original order 
    in the given sentence.

extra:
in resultant sentence:
1. the first letter of the first word 
    is capital.
2. the first letter of the given sentence
    if given capital, is not capital unless
    it is the first word again.
2. if the last character is period, 
    resultant sentence also has that.

*/

#include <iostream>
#include <map>
#include <vector>
using namespace std;

string arrange(string sentence) {
    map<int, vector<string>> words_;
    string tmp = "";
    for (int i = 0; i < (int)sentence.length(); i++) {
        if (sentence[i] != ' ' && isalpha(sentence[i]))
            tmp += tolower(sentence[i]);
        else {
            if (words_.find(tmp.length()) == words_.end())
                words_[tmp.length()] = {tmp};
            else
                words_[tmp.length()].push_back(tmp);
            tmp.clear();
        }
    }
    if (tmp != "") {
        if (words_.find(tmp.length()) == words_.end())
                words_[tmp.length()] = {tmp};
        else
            words_[tmp.length()].push_back(tmp);
    }
    
    string res_sent = "";
    for (auto &i : words_) {
        for (auto &j : i.second) {
            res_sent += j + " ";
        }
    }
    res_sent.pop_back();
    res_sent[0] = toupper(res_sent[0]);
    if (sentence.back() == '.')
        res_sent.push_back('.');
    return res_sent;
}

int main () {
    string sentence = "Cats and dogs.";
    cout << arrange (sentence) << endl;
    return -1;
}
