#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;


int main(){
	int n, m, u, v, w;
	while (cin >> n >> m && (n || m)){
		vvii AdjList(n, vii());
		for (int i = 0; i < m; ++i){
			cin >> u >> v >> w;
			AdjList[u].push_back(ii(v, w));
			AdjList[v].push_back(ii(u, w));
		}

		priority_queue<ii, vii, greater<ii> > pq; pq.push(ii(0, 0));
		vi vis(n, 0);
		int m = 0;
		while (pq.size()){
			ii f = pq.top();
			pq.pop();
			if (vis[f.second]) continue;
			vis[f.second] = 1;
			m = max(m, f.first);
			for (auto &e : AdjList[f.second]){
				pq.push(ii(e.second, e.first));
			}
		}
		bool possible = true;
		for (auto &i : vis) possible &= i;
		if (possible) cout << m << endl;
		else cout << "IMPOSSIBLE" << endl;
	}
}