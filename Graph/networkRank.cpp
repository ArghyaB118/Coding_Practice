/* LC#1615

There is an infrastructure of n cities 
with some number of roads connecting these cities. 
Each roads[i] = [ai, bi] 
indicates that there is a bidirectional 
road between cities ai and bi.

The network rank of two different cities 
is defined as the total number of directly 
connected roads to either city. 
If a road is directly connected to both cities, 
it is only counted once.

The maximal network rank of the infrastructure 
is the maximum network rank of 
all pairs of different cities.

Given the integer n and the array roads, 
return the maximal network rank 
of the entire infrastructure.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// beats ~20% LC users
int maximalNetworkRank(int n, vector<vector<int>>& roads) {
	unordered_map<int, unordered_set<int>> edges;
	for (int i = 0; i < n; i++)
		edges.insert({i, {}});
	
	for (auto &r : roads) {
		edges[r[0]].insert(r[1]);
		edges[r[1]].insert(r[0]);
	}
	
	int rank = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (edges[i].find(j) != edges[i].end())
				rank = max(rank, (int)edges[i].size() + (int)edges[j].size() - 1);
			else
				rank = max(rank, (int)edges[i].size() + (int)edges[j].size());
		}
	}
	return rank;
}

int main () {
	
	return 0;
}