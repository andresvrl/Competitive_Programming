#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;

int depth;
vvi tree;
vi p;
ii off_edge;

void dfs(int u, int d, int &res){
	if (d >= depth) depth = d, res = u;
	for (auto &v : tree[u]){
		if (p[v] == 0 && ii(u,v) != off_edge && ii(v,u) != off_edge){
			p[v] = u;
			dfs(v, d + 1, res);
		}
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int start, fin;
	int tc, n, a, b;
	cin >> tc;
	while (tc--){
		cin >> n;
		vector<ii> edges;
		tree = vvi(n + 1, vi());
		p = vi(n + 1, 0);
		for (int i = 1; i < n; i++){
			cin >> a >> b;
			edges.push_back(ii(a, b));
			tree[a].push_back(b);
			tree[b].push_back(a);
		}
		ii cancel, newf, tmpf;
		int first_diam, second_diam;
		int cur_min = 1001001001;

		for (auto &e : edges){
			off_edge = e;

			depth = 0;
			fill(p.begin(), p.end(), 0);
			p[e.first] = -1;
			dfs(e.first, 0, start);

			depth = 0;
			fill(p.begin(), p.end(), 0);
			p[start] = -1;
			dfs(start, 0, fin);

			first_diam = depth;
			vi path;
			while (p[fin] != -1) path.push_back(fin), fin = p[fin];
			path.push_back(start);

			tmpf.first = path[path.size() / 2];
			

			depth = 0;
			fill(p.begin(), p.end(), 0);
			p[e.second] = -1;
			dfs(e.second, 0, start);

			depth = 0;
			fill(p.begin(), p.end(), 0);
			p[start] = -1;
			dfs(start, 0, fin);

			second_diam = depth;

			vi path2;
			while (p[fin] != -1) path2.push_back(fin), fin = p[fin];
			path2.push_back(start);

			tmpf.second = path2[path2.size() / 2];

			if (max(first_diam, max(second_diam, ((first_diam + 1) / 2) + ((second_diam + 1) / 2) + 1)) < cur_min){
				cancel = e;
				newf = tmpf;
				cur_min = max(first_diam, max(second_diam, ((first_diam + 1) / 2) + ((second_diam + 1) / 2) + 1));
			}
		}
		
		cout << cur_min << endl;
		cout << cancel.first << " " << cancel.second << endl;
		cout << newf.first << " " << newf.second << endl;

		
	}
}