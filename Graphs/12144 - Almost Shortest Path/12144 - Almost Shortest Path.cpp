#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>
#include <set>

using namespace std;
typedef  pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
const int INF = 1000000000;

int main(){
	int N, M, S, D, U, V, P;
	while (cin >> N >> M && (N || M)){
		cin >> S >> D;
		vvii AdjList(N, vii());
		for (int i = 0; i < M; ++i){
			cin >> U >> V >> P;
			AdjList[U].push_back(ii(V, P));
		}

		vvi sp_edges(N, vi());
		vi dist(N, INF); dist[S] = 0;
		priority_queue<ii, vii, greater<ii>> q;
		q.push(ii(0, S));
		while (!q.empty()){
			ii f = q.top();
			q.pop();
			int u = f.second, d = f.first;
			if (d > dist[u]) continue;
			for(int i = 0; i < AdjList[u].size(); ++i){
				ii e = AdjList[u][i];
				int v = e.first, w = e.second;
				if (dist[v] > dist[u] + w){
					sp_edges[v].clear();
					sp_edges[v].push_back(u);
					dist[v] = dist[u] + w;
					q.push(ii(dist[v], v));
				}
				else if (dist[v] == dist[u] + w){
					sp_edges[v].push_back(u);
				}
			}
		}

		vvi forbidden(N, vi(N, 0));
		queue<int> que; que.push(D);
		while (!que.empty()){
			int u = que.front();
			que.pop();
			for (int i = 0; i < sp_edges[u].size(); ++i){
				que.push(sp_edges[u][i]);
				forbidden[sp_edges[u][i]][u] = 1;
			}
		}


		vi dist2(N, INF); dist2[S] = 0;
		priority_queue<ii, vii, greater<ii>> q2;
		q2.push(ii(0, S));
		while (!q2.empty()){
			ii f = q2.top();
			q2.pop();
			int u = f.second, d = f.first;
			if (d > dist2[u]) continue;
			for (int i = 0; i < AdjList[u].size(); ++i){
				ii e = AdjList[u][i];
				int v = e.first, w = e.second;
				if (forbidden[u][v])  continue;
				if (dist2[v] > dist2[u] + w){
					dist2[v] = dist2[u] + w;
					q2.push(ii(dist2[v], v));
				}
			}
		}

		if (dist2[D] != INF) cout << dist2[D] << endl;
		else cout << -1 << endl;
	}
}