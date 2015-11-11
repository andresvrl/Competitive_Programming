#include <iostream>
#include <unordered_map>

using namespace std;
typedef long long ll;

unordered_map<ll, ll> dp;

ll low_pow2(ll a){
	ll ans = 1;
	for (int i = 0; i < 64; i++){
		if ((ans << 1) >= a) break;
		else ans <<= 1;
	}
	return ans;
}

ll solve(ll a){
	if (a == 0) return 0;
	if (dp.count(a)) return dp[a];
	ll low2 = low_pow2(a);
	return dp[a] = solve(low2) + solve(a - low2) + (a - low2);
}

int main(){
	dp[0] = 0, dp[1] = 0, dp[2] = 1, dp[3] = 2, dp[4] = 4;
	ll a, b;
	while (cin >> a >> b){
		cout << solve(b + 1) - solve(a) << endl;
	}
}