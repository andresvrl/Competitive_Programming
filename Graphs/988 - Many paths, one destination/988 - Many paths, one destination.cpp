#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi adjlist;
vi topo;
vi vis;

void tsort(int p){
	if (vis[p]) return;
	vis[p] = 1;
	for (auto &u : adjlist[p])
		tsort(u);
	topo.push_back(p);
}

int main(){
	int n;
	bool first = true;
	while (cin >> n){
		vi deaths;
		topo.clear();
		vis.assign(n, 0);
		adjlist.clear();
		adjlist.assign(n, vi());
		int c, e;
		for (int i = 0; i < n; i++){
			cin >> c;
			if (c == 0) deaths.push_back(i);
			for (int j = 0; j < c; j++){
				cin >> e;
				adjlist[i].push_back(e);
			}
		}
		tsort(0);
		vi paths(n, 0); paths[0] = 1;
		for (int i = topo.size() - 1; i >= 0; i--){
			for (auto &u : adjlist[topo[i]]){
				paths[u] += paths[topo[i]];
			}
		}
		int ways = 0;
		if (first) first = false;
		else cout << endl;
		for (auto &i : deaths) ways += paths[i];
		cout << ways << endl;
	}
}
