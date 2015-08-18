#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;


int R, C, m, n;
int W;
int a, b;
vvi grid;
vi h;
vi v;
int casenum = 1;


void solve(){
	pair<int, int> pos = { 0, 0 };
	queue<pair<int, int> > cola;
	vi globalCount = { 0, 0 };
	cola.push(pos);
	grid[0][0] = 1;
	while (cola.size()){
		pos = cola.front(); cola.pop();
		int x = pos.first, y = pos.second;
		int cont = 0;
		int dx, dy;
		for (int i = 0; i < h.size(); i++){
			dx = x + h[i];
			dy = y + v[i];
			if (dx >= 0 && dy >= 0 && dx < R&&dy < C&&grid[dx][dy] != -1){
				cont++;
				if (!grid[dx][dy]){
					grid[dx][dy] = 1;
					cola.push(ii(dx, dy));
				}
			}
		}
		globalCount[cont % 2]++;
	}
	cout << "Case " << casenum++ << ": " << globalCount[0] << " " << globalCount[1] << endl;
}


int main() {

	int T;
	cin >> T;
	while (T--){
		cin >> R >> C >> m >> n;

		grid = vvi(R, vi(C, 0));
		if (m != 0 && n != 0 && n != m){
			h = { m, m, -m, -m, n, n, -n, -n };
			v = { n, -n, n, -n, m, -m, m, -m };
		}
		else if (n == 0){
			h = { m, -m, n, n};
			v = { n, n, m, -m };
		}
		else if (m == 0){
			h = { m, m, n, -n };
			v = { n, -n, m, m };
		}
		else if (m == n){
			h = { m, m, -m, -m };
			v = { m, -m, m, -m };
		}
		cin >> W;
		for (int i = 0; i < W; i++){
			cin >> a >> b;
			grid[a][b] = -1;
		}

		solve();
	}

}