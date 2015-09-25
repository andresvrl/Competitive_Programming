#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;

int gcd(int a, int b) {
	int tmp;
	while (b){ a %= b; tmp = a; a = b; b = tmp; }
	return a;
}

vi color;
vector<ii> center;
vi radi;
vector<vi> AdjList;

void dfs(int u){
	for (auto &i : AdjList[u]){
		if (color[i] == -1){
			color[i] = (color[u] + 1) % 2;
			dfs(i);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int tc, n, a, b, c;
	int min_x, max_x, min_y, max_y, dist;
	cin >> tc;
	while (tc--){
		cin >> n;
		AdjList.assign(n, vi());
		color = vi(n, -1);
		radi = vi(n);
		center = vector<ii>(n);
		for (int i = 0; i < n; ++i){
			cin >> a >> b >> c;
			a += 10000;
			b += 10000;
			radi[i] = c;
			center[i] = ii(a, b);
		}

		for (int i = 0; i < n; i++){
			for (int j = i + 1; j < n; j++){
				max_x = max(center[j].first, center[i].first);
				min_x = min(center[j].first, center[i].first);
				max_y = max(center[j].second, center[i].second);
				min_y = min(center[j].second, center[i].second);
				dist = (max_x - min_x) * (max_x - min_x) + (max_y - min_y) * (max_y - min_y);
				if (dist == (radi[i] + radi[j]) * (radi[i] + radi[j])){
					AdjList[i].push_back(j);
					AdjList[j].push_back(i);
				}
			}
		}

		color[0] = 0;
		dfs(0);

		for (int i = 0; i < n; ++i){
			if (color[i] == -1) cout << "not moving" << endl;
			else{
				a = radi[0];
				b = radi[i];
				c = gcd(a, b);
				a /= c;
				b /= c;
				if (b == 1) cout << a << ((color[i] == 0) ? " clockwise" : " counterclockwise") << endl;
				else{
					cout << a << "/" << b << ((color[i] == 0) ? " clockwise" : " counterclockwise") << endl;
				}
			}
		}

	}
}