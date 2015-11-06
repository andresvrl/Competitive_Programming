#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef pair<int, ii> iii;
typedef vector<iii> viii;
typedef vector<viii> vviii;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n, m, p, u, v, d, c, s, e, q;
	cin >> n >> m;
	vi prices(n);
	for (int i = 0; i < n; i++) cin >> prices[i];
	vvii g(n);
	for (int i = 0; i < m; i++){
		cin >> u >> v >> d;
		g[u].push_back(ii(v, d));
		g[v].push_back(ii(u, d));
	}
	cin >> q;
	for (int query = 0; query < q; query++){
		cin >> c >> s >> e;
		
		bool found = false;
		int ans = 987654321;
		vvi dist(n, vi(c + 1, 987654321));
		dist[s][0] = 0;
		priority_queue<iii, vector<iii>, greater<iii>> pq; pq.push(iii(0, ii(s, 0))); //cost, location, fuel
		while (!pq.empty()){
			iii f = pq.top(); pq.pop();
			int cost = f.first;
			int location = f.second.first;
			int fuel = f.second.second;
			if (location == e){
				ans = min(ans, cost);
				found = true;
			}
			if (dist[location][fuel] < cost) continue;
			
			if (fuel < c && dist[location][fuel + 1] > cost + prices[location]){
				dist[location][fuel + 1] = cost + prices[location];
				pq.push(iii(cost + prices[location], ii(location, fuel + 1)));
			}
			for (auto &v : g[location]){
				if (fuel >= v.second && dist[v.first][fuel - v.second] > cost){
					dist[v.first][fuel - v.second] = cost;
					pq.push(iii(cost, ii(v.first, fuel - v.second)));
				}
			}
		}
		if (!found) cout << "impossible" << endl;
		else cout << ans << endl;
	}
}