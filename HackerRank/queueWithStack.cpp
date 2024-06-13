#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

class myqueue {
private:
    stack<int> ingoers, outgoers;
public:
    myqueue() {
        this->ingoers = {};
        this->outgoers = {};
    }
    void enqueue(int x) {
        // cout << x << endl;
        this->ingoers.push(x);
    }
    int dequeue() {
        if (this->outgoers.empty()) {
            while (!this->ingoers.empty()) {
                this->outgoers.push(ingoers.top());
                this->ingoers.pop();
            }
        }
        int x = outgoers.top();
        this->outgoers.pop();
        return x;
    }
    int print() {
        if (this->outgoers.empty()) {
            while (!this->ingoers.empty()) {
                this->outgoers.push(ingoers.top());
                this->ingoers.pop();
            }
        }
        return outgoers.top();
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    myqueue* qq = new myqueue();
    string line;
    getline(cin, line);
    int q = stoi(line);
    while (q > 0) {
        getline(cin, line);
        if (line == "2")
            qq->dequeue();
        else if (line == "3")
            cout << qq->print() << endl;
        else if (line[0] == '1') {
            int x = line.length();
            int y = stoi(line.substr(2, x - 2));
            // cout << y << endl;
            qq->enqueue(y);
            // cout << "here" << endl;
        }
        q--;
    }
    return 0;
}
