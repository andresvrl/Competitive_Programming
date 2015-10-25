#include <iostream>
#include <string.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;
typedef pair<int, int> ii;

int grid[1005][1005];
int x, y, t, l, w;
//		right, down, left, up
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };


bool valid(int i, int j, int time){
	return (i >= 0 && i < y && j >= 0 && j < x && (grid[i][j] == 0 || grid[i][j] > time));
}

int main(){
	while (cin >> x >> y >> t >> l >> w && x){
		memset(grid, 0, sizeof grid);
		int row1, row2, col1, col2;
		set<ii> leaks;
		for (int i = 0; i < l; i++){
			cin >> col1 >> row1;
			leaks.insert(ii(row1 - 1, col1 - 1));
		}
		for (int i = 0; i < w; i++){
			cin >> col1 >> row1 >> col2 >> row2;
			col1--, col2--, row1--, row2--;
			int difx = col2 - col1;
			int dify = row2 - row1;
			if (difx) difx /= abs(difx);
			if (dify) dify /= abs(dify);
			grid[row2][col2] = -1;
			for (int col = col1, row = row1; col != col2 || row != row2; col += difx, row += dify)
				grid[row][col] = -1;
			
		}
		int ans = 0;
		for (int i = 1; i <= t; i++){
			set<ii> nextLeaks;
			for (auto &leak : leaks){
				if (!grid[leak.first][leak.second]) ans++;
				grid[leak.first][leak.second] = i;
				for (int j = 0; j < 4; j++){
					if (valid(leak.first + dy[j], leak.second + dx[j], i + 1)){
						nextLeaks.insert(ii(leak.first + dy[j], leak.second + dx[j]));
					}
				}
			}
			leaks = nextLeaks;
		}
		cout << ans << endl;
	}
}