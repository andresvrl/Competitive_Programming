#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
using namespace std;

typedef vector<int> vi;

const int MAX_V = 205;
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
	int n, m, s, e ,c;
	while (cin >> n >> m){
		memset(res, 0, sizeof res);
		source = 1; target = m;
		AdjList.assign(m + 1, vi());
		for (int i = 0; i < n; ++i){
			cin >> s >> e >> c;
			AdjList[s].push_back(e);
			AdjList[e].push_back(s);
			res[s][e] += c;
		}
		cout << maxflow() << endl;
	}
}


