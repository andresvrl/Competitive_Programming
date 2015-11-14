#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
using namespace std;

typedef vector<int> vi;

const int MAX_V = 105;
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
	int n;
	int tc = 1;
	while (cin >> n && n){
		memset(res, 0, sizeof res);
		AdjList.assign(n + 5, vi());
		int c;
		cin >> source >> target >> c;
		int u, v, b;
		for (int i = 0; i < c; i++){
			cin >> u >> v >> b;
			if (res[u][v] == 0){
				AdjList[u].push_back(v);
				AdjList[v].push_back(u);
			}
			res[u][v] += b;
			res[v][u] += b;
		}
		cout << "Network " << tc++ << endl << "The bandwidth is " << maxflow() << "." << endl << endl;
	}
	
}


