#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

vvii AdjList;
vi dist;
vi friends;

ii dfs(int u){
	ii res(0, 0), tmp(0, 0);
	int reachable = 0;
	for (auto &v : AdjList[u]){
		if(res.first == 0) dist[v.first] = dist[u] + v.second;
		else dist[v.first] = v.second;
		tmp =  dfs(v.first);	
		if (tmp.first) res.second = max(v.second + tmp.second, res.second);
		res.first += tmp.first;
	}
	if (res.first){ dist[u] = 0; }
	return ii(friends[u] || res.first, res.second);

}

int main(){
	int n, f, a, b, c, l;
	while (cin >> n >> f){
		AdjList.assign(n + 1, vii());
		dist.assign(n + 1, 0);
		friends.assign(n + 1, 0);
		for (int i = 0; i < n - 1; ++i){
			cin >> a >> b >> c;
			AdjList[a].push_back(ii(b, c));
		}

		
		for (int i = 0; i < f; ++i){
			cin >> l;
			friends[l] = 1;
		}

		ii res = dfs(1);

		int t = 0;
		for (int i = 0; i <= n; ++i){
			if (friends[i]){
				t += dist[i];
			}
		}

		cout << t - res.second << endl;
	}
}