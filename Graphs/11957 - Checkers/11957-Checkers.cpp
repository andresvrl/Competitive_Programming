#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;
typedef pair<int, int> ii;

int dr[] = { -1, -1, -2, -2 };
int dc[] = { -1, 1, -2, 2 };
int ways[105][105];
vector<string> board;
string str;
int t, n, ans;

void go(int r, int c){
	int nc = 0, nr = 0;
	for (int i = 0; i < 4; ++i){
		nr = r + dr[i];
		nc = c + dc[i];
		if (nr < 0 || nc < 0 || nr >= n || nc >= n)
			continue;
		if (i < 2 && board[nr][nc] == '.')
			ways[nr][nc] = (ways[r][c] + ways[nr][nc]) % 1000007;
		if (i == 2 && board[r - 1][c - 1] == 'B' && board[nr][nc] == '.')
			ways[nr][nc] = (ways[r][c] + ways[nr][nc]) % 1000007;
		if (i == 3 && board[r - 1][c + 1] == 'B' && board[nr][nc] == '.')
			ways[nr][nc] = (ways[r][c] + ways[nr][nc]) % 1000007;
	}
}

int main(){
	cin >> t;
	for(int tc = 1; tc <= t; ++tc){
		memset(ways, 0, sizeof(ways[0][0]) * 105 * 105);
		cin >> n;
		board.clear();
		for (int i = 0; i < n; ++i){
			cin >> str;
			board.push_back(str);
		}
		ii w;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (board[i][j] == 'W')
					w = ii(i, j);
		ways[w.first][w.second] = 1;
		for (int r = n - 1; r >= 0; --r)
			for (int c = 0; c < n; ++c)
				go(r, c);
		ans = 0;
		for (int i = 0; i < n; ++i)
			ans = (ans + ways[0][i]) % 1000007;
		cout << "Case " << tc << ": " << ans << endl;
	}
}