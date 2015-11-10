#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

vvi tree;
vi p;
int memo[2][100005];

int mvc(int n, int t){
	if (memo[t][n] != -1) return memo[t][n];
	if (tree[n].size() == 0) return t;
	int ans = t;
	if (t){
		for (auto &u : tree[n]){
			if (p[n] != u){
				p[u] = n;
				ans += min(mvc(u, true), mvc(u, false));
			}
		}
	}
	else{
		for (auto &u : tree[n]){
			if (p[n] != u){
				p[u] = n;
				ans += mvc(u, true);
			}
		}
	}
	return memo[t][n] = ans;
}

int main(){
	memset(memo, -1, sizeof memo);
	int nodes, u , v;
	cin >> nodes;
	tree = vvi(nodes, vi());
	p = vi(nodes, -1);
	for (int i = 1; i < nodes; i++){
		cin >> u >> v;
		tree[u - 1].push_back(v - 1);
		tree[v - 1].push_back(u - 1);
	}
	cout << min(mvc(0, 0), mvc(0, 1)) << endl;
}