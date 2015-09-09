#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
using namespace std;

typedef vector<int> vi;

const int MAX_V = 1000;
const int INF = 1000000000;

int res[MAX_V][MAX_V], source, target;
vi p, vis;
vector<vi> AdjList;

int maxflow(){
	int mf = 0;
	while (1) {
		queue<int> q; q.push(source);
		p.assign(MAX_V, -1);
		vis.assign(MAX_V, 0);
		vis[source] = 1;
		while (!q.empty() && p[target] == -1) {
			int u = q.front(); q.pop();
			for (int i = 0; i < AdjList[u].size(); ++i){
				int v = AdjList[u][i];
				if (res[u][v] > 0 && !vis[v])
					q.push(v), p[v] = u, vis[v] = 1;
			}
		}
		if (p[target] == -1) break;
		int flow = INF; // bottleneck
		for (int v = target; p[v] != -1; v = p[v])
			flow = min(flow, res[p[v]][v]);
		for (int v = target; p[v] != -1; v = p[v])
			res[p[v]][v] -= flow, res[v][p[v]] += flow;

		mf += flow;
	}
	return mf;
}

int main() {
	int n, m, s, u;
	while (cin >> n >> m){
		source = n + m + 2;
		target = source + 1;
		memset(res, 0, sizeof res);
		AdjList.assign(n+m+5, vi());
		for (int i = 0; i < n; ++i){
			AdjList[source].push_back(i);
			res[source][i] = 1;
		}
		for (int i = n + 1; i <= n + m; ++i){
			AdjList[target].push_back(i);
			AdjList[i].push_back(target);
			res[i][target] = 1;
		}
		for (int i = 0; i < n; ++i){
			cin >> s;
			for (int j = 0; j < s; ++j){
				cin >> u;
				AdjList[i].push_back(n + u);
				AdjList[n + u].push_back(i);
				res[i][n + u] = 1;
			}
		}
		cout << maxflow() << endl;
	}
	
}


