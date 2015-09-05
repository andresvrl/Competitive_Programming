#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;
int v, p, s;
int villages[305];
int dp[305][35];
int cost[305][305];
const int INF = 1000000000;

int solve(int prev, int posts){
	if (dp[prev][posts] != -1) return dp[prev][posts];
	if (posts == 0){
		return cost[prev][v + 1];
	}
	int best = INF;
	for (int i = prev + 1; i <= v; ++i){
		best = min(best, solve(i, posts - 1) + cost[prev][i]);
	}
	return dp[prev][posts] = best;
}

int main(){
	cin >> v >> p;
	for (int i = 1; i <= v; ++i) cin >> villages[i];
	villages[0] = -INF;
	villages[v + 1] = INF;
	for (int i = 0; i < v; ++i){
		cost[i][i] = 0;
		cost[i][i + 1] = 0;
		for (int j = i + 2; j <= v + 1; ++j){
			s = 0;
			for (int k = j - 1; k > i; --k){
				s += min(villages[k] - villages[i], villages[j] - villages[k]);
			}
			cost[i][j] = s;
		}
	}
	memset(dp, -1, sizeof(dp[0][0]) * 305 * 35);
	cout << solve(0, p) << endl;
}