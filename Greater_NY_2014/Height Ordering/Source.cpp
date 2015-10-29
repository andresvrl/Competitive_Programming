#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int main(){
	int n, k;
	cin >> n;
	for(int tc = 0; tc < n; tc++){
		cin >> k;
		ll ans = 0;
		vector<ll> v(20);
		ll s;
		for (ll i = 0; i < 20; i++){
			cin >> s;
			ll j = 0;
			for (; j < i; j++){
				if (v[j] > s) break;
			}
			ans += (i - j);
			for (ll k = i; k > j; k--) v[k] = v[k - 1];
			v[j] = s;
		}
		cout << k << " " << ans << endl;
	}
}