/* LC#636

On a single-threaded CPU, 
we execute a program containing n functions. 
Each function has a unique ID between 0 and n-1.

Function calls are stored in a call stack: 
when a function call starts, 
its ID is pushed onto the stack, 
and when a function call ends, 
its ID is popped off the stack. 
The function whose ID is at the top of the stack 
is the current function being executed. 
Each time a function starts or ends, 
we write a log with the ID, 
whether it started or ended, and the timestamp.

You are given a list logs, where logs[i] represents 
the ith log message formatted as a string 
"{function_id}:{"start" | "end"}:{timestamp}". 
For example, "0:start:3" means a function call 
with function ID 0 started at the beginning of timestamp 3, 
and "1:end:2" means a function call with function ID 1 
ended at the end of timestamp 2. 
Note that a function can be called multiple times, 
possibly recursively.

A function's exclusive time is the sum of 
execution times for all function calls in the program. 
For example, if a function is called twice, 
one call executing for 2 time units 
and another call executing for 1 time unit, 
the exclusive time is 2 + 1 = 3.

Return the exclusive time of each function 
in an array, 
where the value at the ith index represents 
the exclusive time for the function with ID i.
*/

#include <iostream>
#include <string>
#include <stack>
using namespace std;

// beats ~91% LC users
struct entry {
	int id;
	string ops;
	int runtime = 0;
};

entry processEntry (string s) {
	entry e;
	string tmp = "";
	for (auto &ch : s) {
		if (ch != ':')
			tmp += ch;
		else if (ch == ':' 
			&& (tmp != "start" && tmp != "end")) {
			e.id = stoi(tmp);
			tmp.clear();
		}
		else if (ch == ':' 
			&& (tmp == "start" || tmp == "end")) {
			e.ops = tmp;
			tmp.clear(); 
		}
	}
	e.runtime = stoi(tmp);
	return e;
}

vector<int> exclusiveTime(int n, vector<string>& logs) {
	vector<int> runtimes(n, 0);
	stack<entry> st;
	st.push(processEntry(logs[0]));
	for (int i = 1; i < logs.size(); i++) {
		entry e = processEntry(logs[i]);
		if (e.ops == "start") {
			if (!st.empty()) {
				runtimes[st.top().id] += (e.runtime - st.top().runtime);
			}
			st.push(e);
		}
		else {
			runtimes[e.id] += (e.runtime - st.top().runtime + 1);
			st.pop();
			if (!st.empty())
				st.top().runtime = e.runtime + 1;
		}
	}
	return runtimes;
}

int main () {
	int n = 2;
	vector<string> logs = {"0:start:0","1:start:2","1:end:5","0:end:6"};
	vector<int> runtimes = exclusiveTime(n, logs);
	for (int &i : runtimes)
		cout << i << " ";
	cout << endl;
	return 0;
}