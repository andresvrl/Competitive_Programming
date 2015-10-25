#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ll;

//n = num of entries, no repetitions, k starts at 0
vector<ll> kth_permutation(ll n, ll k){
	ll fact[21];
	fact[0] = 1;
	for (ll i = 1; i < n; i++) fact[i] = fact[i - 1] * i;

	vector<ll> perm(n);
	for (ll i = 0; i < n; i++){
		perm[i] = k / fact[n - 1 - i];
		k = k % fact[n - 1 - i];
	}

	for (ll i = n - 1; i > 0; --i)
		for (ll j = i - 1; j >= 0; --j)
			if (perm[j] <= perm[i])
				perm[i]++;
	
	return perm;
}


//nth permutation with repeated char, n starts at 0
string nth_permutation_rep(string s, ll n){
	vector<int> rep(s.size(), 0);
	rep[0] = 1; 
	sort(s.begin(), s.end());
	string unique; unique += s[0];
	for (int i = 1; i < s.size(); i++){
		if (s[i] != s[i - 1]){
			rep[unique.length()] = 1;
			unique += s[i];
		}
		else rep[unique.length() - 1]++;
	}

	ll fact[21];
	fact[0] = 1;
	for (ll i = 1; i < 21; i++) fact[i] = fact[i - 1] * i;

	string ans;
	for (int i = 0; i < s.size(); i++){
		for (int j = 0; j < unique.size(); j++){
			if (rep[j] > 0){
				rep[j]--;
				ll f = fact[s.size() - i - 1];
				for (int k = 0; k < rep.size(); k++)
					f /= fact[rep[k]];
				if (f > n){
					ans += unique[j];
					break;
				}
				rep[j]++;
				n -= f;
			}
		}
	}
	return ans;
}

int main(){
	string s;
	ll k;
	while (cin >> s >> k && s != "#"){
		cout << nth_permutation_rep(s, k - 1);
		cout << endl;
	}
}