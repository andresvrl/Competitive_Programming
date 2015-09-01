#include <iostream>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<int, ii> edge;
typedef vector<edge> ve;
const int INF = 1000000000;

int main(){
	int n, r, s, d, w, q, tmp;
	int x = 1;
	while (scanf("%d", &n) == 1){
		vi b(n);
		for (int i = 0; i < n; ++i)
			cin >> b[i];
		ve el;
		cin >> r;
		for (int i = 0; i < r; ++i){
			cin >> s >> d;
			s--; d--;
			w = b[d] - b[s];
			el.push_back(edge(w * w * w, ii(s, d)));
		}
		vi dist(n, INF); dist[0] = 0;
		bool relaxed = true;
		for (int i = 0; i < n - 1 && relaxed; ++i){
			relaxed = false;
			for (auto &e : el){
				int u = e.second.first, v = e.second.second, w = e.first;
				if (dist[v] > dist[u] + w){
					dist[v] = dist[u] + w;
					relaxed = true;
				}
			}
		}

		vi cyc(n, 0);
		relaxed = true;
		for (int i = 0; i < n - 1 && relaxed; ++i){
			relaxed = false;
			for (auto &e : el){
				int u = e.second.first, v = e.second.second, w = e.first;
				if (dist[v] > dist[u] + w){
					dist[u] = -INF;
					dist[v] = -INF;
					relaxed = true;
				}
			}
		}

		printf("Set #%d\n", x++);
		cin >> q;
		for (int i = 0; i < q; ++i){
			cin >> tmp;
			tmp--;
			if (cyc[tmp] || dist[tmp] < 3 || dist[tmp] > 10000000) cout << "?" << endl;
			else cout << dist[tmp] << endl;
		}
	}
	
}