#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int INF = 1000000000;

int main(){
	int n, en, doors, reachable;
	while (cin >> n && n != -1){
		vi energy(n);
		vvi adj(n, vi());
		for (int i = 0; i < n; ++i){
			cin >> en;
			energy[i] = -en;
			cin >> doors;
			for (int j = 0; j < doors; ++j){
				cin >> reachable;
				--reachable;
				adj[i].push_back(reachable);
			}
		}

		vi dist(n, INF); dist[0] = -100;
		bool relaxed = true;
		for (int i = 0; i < n - 1 && relaxed; ++i){
			relaxed = false;
			for (int u = 0; u < adj.size(); ++u){
				for (int x = 0; x < adj[u].size(); ++x){
					int v = adj[u][x];
					if (dist[v] > dist[u] + energy[v] && 0 > dist[u] + energy[v]){
						relaxed = true;
						dist[v] = dist[u] + energy[v];
					}
				}
			}
		}

		vi vis(n, 0);
		relaxed = true;
		for (int i = 0; i < n - 1 && relaxed; ++i){
			relaxed = false;
			for (int u = 0; u < adj.size(); ++u){
				if (vis[u]) continue;
				for (int x = 0; x < adj[u].size(); ++x){
					int v = adj[u][x];
					if (vis[v]) continue;
					if (dist[v] > dist[u] + energy[v] && 0 > dist[u] + energy[v]){
						relaxed = true;
						queue<int> q;
						q.push(u);
						while (q.size()){
							int f = q.front();
							q.pop();
							if (vis[f]) continue;
							vis[f] = 1;
							for (int k = 0; k < adj[f].size(); ++k){
								q.push(adj[f][k]);
							}
						}
					}
				}
			}
		}
		
		if (dist[n - 1] < 0 || vis[n - 1]) cout << "winnable" << endl;
		else cout << "hopeless" << endl;

	}
}