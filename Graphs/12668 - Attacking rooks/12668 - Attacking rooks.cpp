#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
using namespace std;

typedef vector<int> vi;

const int MAX_V = 10000;
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

int m[105][105];
int R, C;
int labelMatrix(){
	int actual = 1;
	bool inObstacle = true;
	int lastRow = -1;
	for (int i = 0; i < R; i++){
		for (int j = 0; j < C; j++){
			if (m[i][j] != -1){
				inObstacle = false;
				lastRow = m[i][j] = actual;
			}
			else {
				if (!inObstacle) actual++;
				inObstacle = true;
			}
		}
		actual++;
		inObstacle = true;
	}
	actual = lastRow + 1;
	inObstacle = true;
	int lastColumn = -1;
	for (int j = 0; j < C; j++){
		for (int i = 0; i < R; i++){
			if (m[i][j] != -1){
				inObstacle = false;
				lastColumn = actual;
				AdjList[m[i][j]].push_back(actual);
				AdjList[actual].push_back(m[i][j]);
				res[m[i][j]][actual] = 1;
			}
			else {
				if (!inObstacle) actual++;
				inObstacle = true;
			}
		}
		actual++;
		inObstacle = true;
	}
	//FINISH GRAPH
	source = 0;
	target = lastColumn + 1;
	for (int i = 1; i <= lastRow; i++){
		res[source][i] = 1;
		AdjList[source].push_back(i);
	}
	for (int i = lastRow + 1; i <= lastColumn; i++){
		res[i][target] = 1;
		AdjList[i].push_back(target);
		AdjList[target].push_back(i);
	}
	return target + 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	AdjList.assign(MAX_V, vi());
	int n;
	char c;
	while (cin >> n){
		R = C = n;
		fill(AdjList.begin(), AdjList.end(), vi());
		memset(m, 0, sizeof m);
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				cin >> c;
				if (c != '.') m[i][j] = -1;
			}
		}
		memset(res, 0, sizeof res);
		labelMatrix();
		cout << maxflow() << endl;
	}

}


