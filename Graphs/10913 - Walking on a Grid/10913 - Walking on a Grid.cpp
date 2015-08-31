#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;

ll grid[80][80];
ll dp[80][80][10][5];//row col lives direction
int dp2[80][80][10][5];
const ll NINF = -20000000000;
int N, k, tc;

ll solve(int row, int col, int lives, int dir){
	if (row < 0 || col < 0 || row >= N || col >= N) return NINF;
	if (grid[row][col] < 0) --lives;
	if (lives < 0) return NINF;
	if (row == 0 && col == 0) return grid[0][0];
	if (dp2[row][col][lives][dir] == tc) return dp[row][col][lives][dir];
	dp[row][col][lives][dir] = NINF;
	ll best = NINF;
	if (dir == 0 || dir == 2) best = max(best, solve(row, col - 1, lives, 0) + grid[row][col]); //left
	if (dir == 1 || dir == 2) best = max(best, solve(row, col + 1, lives, 1) + grid[row][col]); // right
	best = max(best, solve(row - 1, col, lives, 2) + grid[row][col]); //up
	dp2[row][col][lives][dir] = tc;
	return dp[row][col][lives][dir] = best;
}

int main(){
	tc = 1;
	while ((cin >> N >> k) && (N || k)){
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				cin >> grid[i][j];
		ll ans = solve(N - 1, N - 1, k, 0);
		if (ans < -10000000000)
			printf("Case %d: impossible\n", tc++);
		else
			printf("Case %d: %lld\n", tc++, ans);
	}
}