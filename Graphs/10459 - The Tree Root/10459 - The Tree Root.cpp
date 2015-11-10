#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

int start, fin;
int depth;
vvi tree;
vi p;

void dfs1(int u, int d){
	if (d >= depth) depth = d, start = u;
	for (auto &v : tree[u]){
		if (p[v] == -1){
			p[v] = u;
			dfs1(v, d + 1);
		}
	}
}

void dfs2(int u, int d){
	if (d >= depth) depth = d, fin = u;
	for (auto &v : tree[u]){
		if (p[v] == -1){
			p[v] = u;
			dfs2(v, d + 1);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int a, b, c;
	while (cin >> a){
		tree = vvi(a);
		p = vi(a, -1);
		for (int i = 0; i < a; i++){
			cin >> b;
			for (int j = 0; j < b; j++){
				cin >> c;
				c--;
				tree[c].push_back(i);
				tree[i].push_back(c);
			}
		}
		depth = 0; p[0] = -2;
		dfs1(0, 0);
		depth = 0;
		p = vi(a, -1);  p[start] = -2;
		dfs2(start, 0);
		vi path;
		int s = fin;
		while (p[s] != -2) path.push_back(s), s = p[s];
		path.push_back(s);
		//for (auto &i : path) cout << i << "-"; cout << endl;
		vi best;
		if (path.size() % 2) best.push_back(path[path.size() / 2]);
		else{
			best.push_back(min(path[path.size() / 2 - 1], path[path.size() / 2]));
			best.push_back(max(path[path.size() / 2 - 1], path[path.size() / 2]));
		}
		cout << "Best Roots  :";
		for (auto &i : best) cout << " " << i + 1;
		cout << endl;

		vi layer = best;
		p = vi(a, 0); for (auto &i : best) p[i] = 1;
		while (1){
			vi nextLayer;
			for (auto &u : layer){
				for (auto &v : tree[u]){
					if (!p[v]){
						p[v] = 1;
						nextLayer.push_back(v);
					}
				}
			}
			if (nextLayer.size()) layer = nextLayer;
			else break;
		}
		sort(layer.begin(), layer.end());
		cout << "Worst Roots :";
		for (auto &i : layer) cout << " " << i + 1;
		cout << endl;
	}
}