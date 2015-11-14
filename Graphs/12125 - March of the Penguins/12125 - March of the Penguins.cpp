#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
const int MAX_V = 300;
const int INF = 1000000000;
const double eps = 1e-9;

int res[MAX_V][MAX_V], source, target;
int res2[MAX_V][MAX_V];
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

struct ice{
	int x, y, c, p;
	ice(int x_, int y_, int p_, int c_){
		x = x_, y = y_, c = c_, p = p_;
	}
};

int main() {
	//residual graph, res[u][v] = flow from u to v
	int tc;
	cin >> tc;
	while (tc--){
		int n, x, y, c, p, penguins = 0;
		double d;
		cin >> n >> d;
		d *= d;
		memset(res, 0, sizeof res);
		memset(res2, 0, sizeof res2);
		AdjList.assign(n * 2 + 5, vi());
	
		vector<ice> layout;
		for (int i = 0; i < n; i++){
			cin >> x >> y >> p >> c;
			penguins += p;
			layout.push_back(ice(x, y, p, c));
		}
		source = 2 * n + 3;
		for (int i = 0; i < layout.size(); i++){
			ice ic1 = layout[i];
			int u = i * 2;
			AdjList[u].push_back(u + 1);
			AdjList[u + 1].push_back(u);
			res2[u][u + 1] = ic1.c;
			if (ic1.p > 0){
				AdjList[source].push_back(u);
				AdjList[u].push_back(source);
				res2[source][u] = ic1.p;
			}
			for (int j = i + 1; j < layout.size(); j++){
				ice ic2 = layout[j];
				int dist = (((ic2.x - ic1.x) * (ic2.x - ic1.x)) +
					((ic2.y - ic1.y) * (ic2.y - ic1.y)));
				if (dist <= d){
					int v = j * 2;
					AdjList[u + 1].push_back(v);
					AdjList[v].push_back(u + 1);
					AdjList[v + 1].push_back(u);
					AdjList[u].push_back(v + 1);
					res2[u + 1][v] = INF;
					res2[v + 1][u] = INF;
				}
			}
		}
		vector<int> ans;
		for (int i = 0; i < layout.size(); i++){
			target = i * 2;
			for (int j = 0; j < MAX_V; j++) for (int k = 0; k < MAX_V; k++) res[j][k] = res2[j][k];
			int maxf = maxflow();
			if (maxf == penguins) ans.push_back(i);
		}
		if (ans.empty()) cout << "-1" << endl;
		else{
			for (int i = 0; i < ans.size() - 1; i++) cout << ans[i] << " ";
			cout << ans.back() << endl;
		}

	}
	
}


