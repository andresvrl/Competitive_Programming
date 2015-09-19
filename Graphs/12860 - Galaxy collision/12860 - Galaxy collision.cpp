#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;

vvi AdjList;
vi vis;
int bw[2];
vi color;

void dfs(int p){
	vis[p] = 1;
	bw[color[p]]++;
	for (auto &i : AdjList[p]){
		if (!vis[i]){
			color[i] = (color[p] + 1) & 1;
			dfs(i);
		}
	}
}

int main(){
	int n; ll tmp;
	while (scanf("%d", &n) != EOF){
		AdjList.assign(n, vi());
		vis.assign(n, 0);
		color.assign(n, 0);
		vii p(n);
		for (int i = 0; i < n; ++i){
			scanf("%lld %lld", &p[i].first, &p[i].second);
		}

		sort(p.begin(), p.end());

		for (int i = 0; i < n; ++i){
			for (int j = i + 1; j < n; ++j){
				if (p[j].first - p[i].first > 5) break;
				tmp = max(p[j].second, p[i].second) - min(p[j].second, p[i].second);;
				if ((p[j].first - p[i].first) * (p[j].first - p[i].first) + tmp * tmp <= 25){
					AdjList[i].push_back(j);
					AdjList[j].push_back(i);
				}
			}
		}

		int sep = 0;
		for (int i = 0; i < n; ++i){
			bw[0] = 0; bw[1] = 0;
			if (!vis[i]) {
				dfs(i);
				sep += min(bw[0], bw[1]);
			}
		}
		printf("%d\n", sep);
	}
}