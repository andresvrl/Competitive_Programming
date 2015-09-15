#include <string>
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;
string s;
int n, c, dpnum;
int special[2005];

typedef pair<int, int> ii;

ii dp[2005][2005];
int dp2[2005][2005];

ii solve(int L, int R){	
	if (L == R) return ii(special[L], 1);
	if (L + 1 == R){
		if (s[L] == s[R]) return ii(special[L] + special[R], 2);
		else return ii(max(special[L], special[R]), 1);
	}
	if (dp2[L][R] == dpnum) return dp[L][R];
	ii best = ii(0, 0);
	ii tmp = ii(0, 0);
	if (s[L] == s[R]){
		tmp = solve(L + 1, R - 1);
		best.first = tmp.first + special[L] + special[R];
		best.second = tmp.second + 2;
	}
	tmp = solve(L + 1, R);
	best = max(best, tmp);
	tmp = solve(L, R - 1);
	best = max(best, tmp);
	dp2[L][R] = dpnum;
	return dp[L][R] = best;
}

int main(){
	dpnum = 1;
	while (cin >> s){
		memset(special, 0, sizeof special);
		cin >> n;
		for (int i = 0; i < n; ++i){
			cin >> c;
			special[c - 1] = 1;
		}
		++dpnum;
		cout << solve(0, s.length() - 1).second << endl;
	}
}