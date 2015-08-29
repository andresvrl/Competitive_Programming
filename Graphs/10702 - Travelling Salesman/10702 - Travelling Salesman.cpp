#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <stdio.h>

using namespace std;

int G[105][105];
int Ends[105];
int dp[101][1001];
int dp2[101][1001];
int C, S, E, T, tc;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
const int INF = -1000000000;

int solve(int dest, int time){
	if (time == 0){
		if (dest == S) return 0;
		return INF;
	}
	if (dp2[dest][time] == tc) return dp[dest][time];
	dp2[dest][time] = tc;
	dp[dest][time] = INF;
	for (int i = 1; i <= C; ++i){
		if (i == dest) continue;
		dp[dest][time] = max(dp[dest][time], solve(i, time - 1) + G[i][dest]);
	}
	return dp[dest][time];
}

int main(){
	tc = 0;
	while ((cin >> C >> S >> E >> T) && (C || S || E || T)){
		++tc;
		for (int i = 1; i <= C; ++i){
			for (int j = 1; j <= C; ++j){
				scanf("%d", &G[i][j]);
			}
		}
		for (int i = 0; i < E; ++i){
			scanf("%d", &Ends[i]);
		}

		int ans = INF;
		for (int i = 0; i < E; ++i)
			ans = max(ans, solve(Ends[i], T));
		printf("%d\n", ans);
	}
}