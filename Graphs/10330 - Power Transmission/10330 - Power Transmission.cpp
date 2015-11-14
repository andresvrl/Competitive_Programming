#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
using namespace std;

typedef vector<int> vi;

const int MAX_V = 210;
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
			for (auto &v : AdjList[u])
				if (res[u][v] > 0 && !vis[v])
					q.push(v), p[v] = u, vis[v] = 1;
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
	//residual graph, res[u][v] = flow from u to v
	int n, m, u, v, c, b, d;
	while (cin >> n){
		source = n * 2 + 3;
		target = source + 1;
		memset(res, 0, sizeof res);
		AdjList.assign(n * 2 + 10, vi());
		for (int i = 1; i <= n; i++){
			cin >> c;
			AdjList[i].push_back(i + n);
			res[i][i + n] = c;
			AdjList[i + n].push_back(i);
		}
		cin >> m;
		for (int i = 0; i < m; i++){
			cin >> u >> v >> c;
			AdjList[u + n].push_back(v);
			AdjList[v].push_back(u + n);
			res[u + n][v] = c;
		}
		cin >> b >> d;
		for (int i = 0; i < b; i++){
			cin >> v;
			AdjList[source].push_back(v);
			AdjList[v].push_back(source);
			res[source][v] = INF;
		}
		for (int i = 0; i < d; i++){
			cin >> v;
			AdjList[target].push_back(v + n);
			AdjList[v + n].push_back(target);
			res[v + n][target] = INF;
		}

		cout << maxflow() << endl;
	}

}


