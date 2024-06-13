// Assumption: There is only one possible choice

#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;
typedef pair<int, int> prerequisite;

list<int> *adj;
map<int, bool> visited;

void DFS(int s) {
    visited[s] = true; // Mark the current node as visited and print it
    cout << s << " ";    
    list<int>::iterator i; // Recur for all the vertices adjacent to this vertex
    for (i = adj[s].begin(); i != adj[s].end(); ++i)
        if (!visited[*i])
            DFS(*i);
}

void orderOfCourses (vector<prerequisite> prerequisites, int num_courses) {
	for (int i = 0; i < prerequisites.size(); i++)
		adj[prerequisites[i].first].push_back(prerequisites[i].second);

	for (int i = 0; i < num_courses; i++) {
		visited.clear(); DFS(i);
		if (visited.size() == num_courses)
			break;
	}

}

/* LC#207

There are a total of numCourses courses you have to take, 
labeled from 0 to numCourses - 1. 
You are given an array prerequisites 
where prerequisites[i] = [ai, bi] indicates 
that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates 
that to take course 0 you have to first take course 1.
Return true if you can finish all courses. 
Otherwise, return false.
*/

// key insight: can't take a course
// if it is its own prerequisite
// i.e., the graph has a cycle

// Algo: DFS from nodes with incoming edge zero
// edge detected if the dfs 
// returns to a already visited node
/*bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
	unordered_map<int, vector<int>> prereq;
	for (int i = 0; i < numCourses; i++)
		prereq[i] = {};
	for (auto &i : prerequisites)
		prereq[i[0]].push_back(i[1]);
	
	for (int i = 0; i < numCourses; i++) {
		queue<int> q;
        q.push(i);
		while (!q.empty()) {
			int tmp = q.front();
			q.pop();
			for (int j = 0; j < prereq[tmp].size(); j++) {
				if (prereq[tmp][j] == i)
					return false;
				else
					q.push(prereq[tmp][j]);
			}
		}
	}
	return true;
}*/


/* kahn's algorithm
1. store in-degrees of each node
2. store children of each node

3. find nodes of 0 in-degree and enque
4. go to all children and reduce in-degree
i.e. delete the edges from this parent to all the children
5. if any child node now has 0 in-degree, enqueue

6. if you cover n nodes, no cycle, otherwise cyclic DAG.
*/

// beats ~82% LC users
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
	unordered_map<int, vector<int>> prereq;
	vector<int> num_prereq (numCourses, 0);
	for (int i = 0; i < numCourses; i++)
		prereq[i] = {};
	for (auto &i : prerequisites) {
		prereq[i[1]].push_back(i[0]);
		num_prereq[i[0]]++;
	}
    
    for (auto &i : prereq) {
        for (auto &j : i.second)
            cout << j <<  " ";
        cout << endl;
    }
    for (auto &i : num_prereq)
        cout << i << endl;


	queue<int> q;
	for (int i = 0; i < numCourses; i++)
		if (num_prereq[i] == 0)
			q.push(i);
	int count = 0;
	while (!q.empty()) {
		int tmp = q.front();
		q.pop();
		count++;
		for (auto &i : prereq[tmp]) {
			num_prereq[i]--;
			if (num_prereq[i] == 0)
				q.push(i);
		}
	}
    cout << count << endl;
	if (count == numCourses)
		return true;
	return false;
}
int main() {
	int num_courses = 3;
	vector<prerequisite> prerequisites{ make_pair(0,2), make_pair(1,2), make_pair(0,1) }; 
	orderOfCourses(prerequisites, num_courses);
	return 0;
}