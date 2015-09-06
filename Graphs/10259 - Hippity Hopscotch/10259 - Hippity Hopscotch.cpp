#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int grid[105][105];
int dp[105][105];
int dp2[105][105];
int T, n, k, tc;

int solve(int row, int col){
	if (dp2[row][col] == tc) return dp[row][col];
	int best = grid[row][col];
	for (int i = row - k; i <= row + k; ++i){
		if (i < 0 || i >= n || i == row) continue;
		if (grid[i][col] > grid[row][col]){
			best = max(best, solve(i, col) + grid[row][col]);
		}
	}
	for (int j = col - k; j <= col + k; ++j){
		if (j < 0 || j >= n || j == col) continue;
		if (grid[row][j] > grid[row][col]){
			best = max(best, solve(row, j) + grid[row][col]);
		}
	}
	dp2[row][col] = tc;
	return dp[row][col] = best;
}

int main(){
	cin >> T;
	for(tc = 1; tc <= T; ++tc){
		cin >> n >> k;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> grid[i][j];
		if (tc > 1) cout << endl;
		cout << solve(0, 0) << endl;
	}
}