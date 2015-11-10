#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> ii;
const int INF = 1000000000; 
int time_[55][55];
int toll[55][55];
int n, t, tc;

ii dp[55][1005];
ii dp2[55][1005];

ii solve(int state, int rt){
	if (rt < 0) return ii(INF, INF);
	if (state == n - 1) return ii(0, 0);
	if (dp2[state][rt] == ii(tc, tc)) return dp[state][rt];

	ii best = ii(INF, INF);
	ii tmp;
	for (int i = 0; i < n; i++){
		if (i == state) continue;
		tmp = solve(i, rt - time_[state][i]);
		if (tmp.first + toll[state][i] < best.first){
			best.first = tmp.first + toll[state][i];
			best.second = tmp.second + time_[state][i];
		}
	}
	dp2[state][rt] = ii(tc, tc);
	return dp[state][rt] = best;
}


int main(){
	while (cin >> n >> t && n){
		tc++;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				cin >> time_[i][j];
			}
		}
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				cin >> toll[i][j];
			}
		}

		ii ans = solve(0, t);
		cout << ans.first << " " << ans.second << endl;
	}
}