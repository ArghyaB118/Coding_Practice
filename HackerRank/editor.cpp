#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

typedef pair<int, string> ops;

class editor {
private:
	string S;
	stack<ops> undoer;
public:
	editor () { this->S = ""; }
	void append_ (string s_) { 
		this->S += s_;
		this->undoer.push({1, s_});
	}
	void delete_ (int k) {
		this->undoer.push({2, this->S.substr(S.size() - k)});
		this->S.erase(this->S.size() - k);
	}
	void print_ (int k) { cout << this->S[k - 1] << endl; }
	void undo_ () {
		ops p = this->undoer.top(); this->undoer.pop();
		if (p.first == 1)
			this->S.erase(this->S.size() - p.second.size());
		if (p.first == 2)
			this->S += p.second;
	}
};

int main () {
	editor* e = new editor();
	string line;
	while (getline(cin, line)) {
		if (line == "4")
			e->undo_();
		else if (line[0] == '1')
			e->append_(line.substr(2));
		else if (line[0] == '2')
			e->delete_(stoi(line.substr(2)));
		else if (line[0] == '3')
			e->print_(stoi(line.substr(2)));
	}
	return 0;
}