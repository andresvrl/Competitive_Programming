#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vii;
#define DFS_WHITE -1 
#define DFS_BLACK 1
vi dfs_num, dfs_low, scc_id, scc_weight;
vii AdjList, SccAdj;
vi S, visited;                                    // additional global variables
int dfsCounter;
int numSCC;

void tarjanSCC(int u) {
	dfs_low[u] = dfs_num[u] = dfsCounter++;      // dfs_low[u] <= dfs_num[u]
	S.push_back(u);           // stores u in a vector based on order of visitation
	visited[u] = 1;
	for(auto &v :AdjList[u]) {
		if (dfs_num[v] == DFS_WHITE)
			tarjanSCC(v);
		if (visited[v])                                // condition for update
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
	}

	if (dfs_low[u] == dfs_num[u]) {         // if this is a root (start) of an SCC
		while (1) {
			int v = S.back(); S.pop_back(); visited[v] = 0;
			scc_id[v] = numSCC;
			scc_weight[numSCC]--;
			if (u == v) break;
		}
		numSCC++;
	}
}

vi topoSort;             // global vector to store the toposort in reverse order

void dfs(int u) {    // change function name to differentiate with original dfs
	dfs_num[u] = DFS_BLACK;
	for (auto &v: SccAdj[u]) {
		if (dfs_num[v] == DFS_WHITE)
			dfs(v);
	}
	topoSort.push_back(u);
}

int main(){
	int tc, n, g, u, v;
	cin >> tc;
	while (tc--){
		cin >> n >> g;
		
		AdjList.assign(n, vi());
		for (int i = 0; i < g; ++i){
			cin >> u >> v;
			--u; --v;
			AdjList[u].push_back(v);
		}
		if (n == 0){
			cout << 0 << endl;
			continue;
		}
		dfs_num.assign(n, DFS_WHITE);
		dfs_low.assign(n, 0);
		visited.assign(n, 0);
		scc_weight.assign(n, 0);
		scc_id.assign(n, -1);
		dfsCounter = numSCC = 0;
		for (int i = 0; i < n; i++)
			if (dfs_num[i] == DFS_WHITE)
				tarjanSCC(i);
		
		SccAdj.assign(numSCC, vi());
		for (int u = 0; u < n; ++u)
			for (auto &v : AdjList[u])
				if (scc_id[v] != scc_id[u])
					SccAdj[scc_id[u]].push_back(scc_id[v]);
		

		dfs_num.assign(numSCC, DFS_WHITE);
		topoSort.clear();
		for (int i = 0; i < numSCC; i++)
			if (dfs_num[i] == DFS_WHITE)
				dfs(i);

		vi dist(numSCC, 0);
		int best = 1;
		for (int u = topoSort.size() - 1; u >= 0; --u){
			dist[topoSort[u]] = min(dist[topoSort[u]], scc_weight[topoSort[u]]);
			best = min(best, dist[topoSort[u]]);
			for (auto &v : SccAdj[topoSort[u]]){
				dist[v] = min(dist[v], dist[topoSort[u]] + scc_weight[v]);
				best = min(best, dist[v]);
				
			}
		}
		cout << -best << endl;
	}
}