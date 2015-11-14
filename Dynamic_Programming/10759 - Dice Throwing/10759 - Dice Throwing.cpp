#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

ll dp[25][150];
int dp2[25][150];
ll x;
int tc;

ll gcd(ll a, ll b) {
	ll tmp;
	while (b){ a %= b; tmp = a; a = b; b = tmp; }
	return a;
}

ll solve(int dice, ll sum){
	if (dice == 0) return sum >= x ? 1 : 0;
	if (dp2[dice][sum] == tc) return dp[dice][sum];
	ll res = 0;
	for (int i = 1; i <= 6; i++) res += solve(dice - 1, sum + i);
	dp2[dice][sum] = tc;
	return dp[dice][sum] = res;
}

int main(){
	ll n;
	while (cin >> n >> x && n){
		tc++;
		ll space = 1;
		for (int i = 0; i < n; i++) space *= 6;

		ll k = solve(n, 0);
		ll g = gcd(space, k);
		space /= g;
		k /= g;
		if (k == 0) cout << k << endl;
		else if (k == space) cout << 1 << endl;
		else cout << k << "/" << space << endl;
	}
}