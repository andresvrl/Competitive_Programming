#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;
typedef vector<double> vd;
typedef vector<int> vi;

vi cp;
double b, r, v, e, f;
int tc = 0;
double dp[105][105];
int dpnum[105][105];
double expr[10005];
double cost[10005];

inline double t(double x){
	return x >= r ? (1.0 / (v - e*(x - r))) : (1.0 / (v - f*(r - x)));
}

double solve(int start, int end){
	
	if (dpnum[start][end] == tc) return dp[start][end];
	dp[start][end] = cost[cp[end] - cp[start] - 1];
	for (int i = start + 1; i < end; ++i){
		dp[start][end] = min(dp[start][end], solve(start, i) + solve(i, end) + b);
	}
	dpnum[start][end] = tc;
	return dp[start][end];
}

int main(){
	int n, a;

	while (cin >> n && n){
		tc++;
		cp = vi(n+1);
		cp.push_back(0);
		for (int i = 1; i <= n; ++i)
			cin >> cp[i];
		cin >> b >> r >> v >> e >> f;
		for (int i = 0; i <= n; ++i){
			for (int j = 0; j <= n; ++j){
				dp[i][j] = 1000000000.0;
			}
		}
		for (int i = 0; i < 10001; ++i){
			expr[i] = t((double)i);
		}
		cost[0] = expr[0];
		for (int i = 1; i < 10001; ++i){
			cost[i] = expr[i] + cost[i-1];
		}
		printf("%.4lf\n", solve(0, n));
	}
}