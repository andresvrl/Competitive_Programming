#include <iostream>
#include <vector>

using namespace std;

typedef vector<string> vs;
typedef pair<int, int> ii;

int w, h, gold;
vs grid;
vs vis;
int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
int a, b;

void dfs(int x , int y) {
	vis[x][y] = '1';
	if (grid[x][y] == 'G'){
		++gold;
		grid[x][y] = '.';
	}
	for (int i = 0; i < 4; ++i){
		if (grid[x + dx[i]][y+ dy[i]] == 'T'){
			return;
		}
	}
	for (int i = 0; i < 4; ++i){
		if (vis[x + dx[i]][y + dy[i]] == '0' && grid[x + dx[i]][y + dy[i]] != '#'){
			dfs(x + dx[i], y + dy[i]);
		}
	}

}

int main(){
	while (cin >> w >> h){
		gold = 0;
		grid = vs(h, string(w, ' '));
		vis = vs(h, string(w, '0'));
		for (int i = 0; i < h; ++i){
			for (int j = 0; j < w; ++j){
				cin >> grid[i][j];
				if (grid[i][j] == 'P'){
					a = i;
					b = j;
				}
			}
		}
		dfs(a, b);
		cout << gold << endl;
	}
}