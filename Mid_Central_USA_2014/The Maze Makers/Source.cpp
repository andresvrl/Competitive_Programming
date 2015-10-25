#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;
typedef pair<int, int> ii;

bool left(int i){
	return (i & 1) == 0;
}
bool right(int i){
	return (i & (1 << 2)) == 0;
}
bool up(int i){
	return (i & (1 << 3)) == 0;
}
bool down(int i){
	return (i & (1 << 1)) == 0;
}

int main(){
	int h, w;
	while (cin >> h >> w && h){
		string s;
		vector<string> g;
		for (int i = 0; i < h; i++){
			cin >> s;
			g.push_back(s);
		}
		vector<vector<int> > b(h, vector<int>(w, 0));
		ii start, end;
		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				b[i][j] = (g[i][j] >= 'A') ? (g[i][j] - 'A' + 10) : (g[i][j] - '0');
				if (j == 0 && left(b[i][j])) end = start, start = ii(i, j);
				if (j == w - 1 && right(b[i][j])) end = start, start = ii(i, j);
				if (i == 0 && up(b[i][j])) end = start, start = ii(i, j);
				if (i == h - 1 && down(b[i][j])) end = start, start = ii(i, j);
			}
		}
		bool sol = false, reach = true, mult = false;

		vector<vector<bool> > vis(h, vector<bool>(w, false));
		vector<vector<ii> > p(h, vector<ii>(w, ii(-1,-1)));
		queue<ii> q; q.push(start);
		while (!q.empty()){
			ii u = q.front();
			int i = u.first, j = u.second;
			q.pop();
			if (u == end)
				sol = true;
			if (vis[i][j])
				mult = true;
			else{
				vis[i][j] = true;
				ii pa = p[i][j];
				if (pa != ii(i, j - 1) && j > 0 && left(b[i][j])){
					q.push(ii(i, j - 1));
					p[i][j - 1] = u;
				}
				if (pa != ii(i, j + 1) && j < w - 1 && right(b[i][j])){
					q.push(ii(i, j + 1));
					p[i][j + 1] = u;
				}
				if (pa != ii(i - 1, j) && i > 0 && up(b[i][j])){
					q.push(ii(i - 1, j));
					p[i - 1][j] = u;
				}
				if (pa != ii(i + 1, j) && i < h - 1 && down(b[i][j])){
					q.push(ii(i + 1, j));
					p[i + 1][j] = u;
				}
			}
		}

		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				if (!vis[i][j]) reach = false;
			}
		}

		if (!sol) cout << "NO SOLUTION" << endl;
		else if (!reach) cout << "UNREACHABLE CELL" << endl;
		else if (mult) cout << "MULTIPLE PATHS" << endl;
		else cout << "MAZE OK" << endl;
	}
}