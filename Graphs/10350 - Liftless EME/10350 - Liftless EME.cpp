#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;

int g[130][20][20];
int cost[130][20];
int n, m, j, i, k;
const int maxi = 1 << 30;

int solve(int floor, int hole){
	if (floor == 0) return 0;
	if (cost[floor][hole] != maxi) return cost[floor][hole];
	int mini = maxi;
	for (int h = 0; h < m; ++h)
		mini = min(solve(floor - 1, h) + g[floor - 1][h][hole], mini);
	return cost[floor][hole] = mini;
}

int main(){	
	string s;
	while (cin >> s){
		cin >> n >> m;
		for (i = 0; i < n - 1; i++) {//i-floor
			fill(cost[i], cost[i] + 20, maxi);
			for (j = 0; j < m; j++) {//i-floor j-hole
				for (k = 0; k < m; k++) {//i-floor j-hole to i+1-floor k-hole
					cin >> g[i][j][k];
				}
			}
		}
		fill(cost[n-1], cost[n-1] + 20, maxi);
		int ans = maxi;
		for (int h = 0; h < m; ++h)
			ans = min(ans, solve(n - 1, h));

		cout << s << endl;
		cout << ans + (2 * (n - 1))<< endl;
	}
}