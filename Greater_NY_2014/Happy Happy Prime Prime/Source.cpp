#include <iostream>
#include <math.h>
#include <bitset>

using namespace std;
bitset<10001> prime;

void sieve(){
	prime[0] = 1; prime[1] = 1;
	for (int i = 2; i < 10001; i++){
		if (!prime[i]){
			for (int j = i + i; j < 10001; j += i){
				prime[j] = 1;
			}
		}
	}
}

int main(){
	int p, k, n;
	cin >> p;
	sieve();
	while (p--){
		cin >> k >> n;
		if (prime[n]) cout << k << " " << n << " NO" << endl;
		else{
			bool flag = true;
			int it = 1000;
			int cur = n, next = 0;
			int mod;
			while (flag && it--){
				while (cur){
					mod = cur % 10;
					next += mod * mod;
					cur /= 10;
				}
				if (next == 1) flag = false;
				else{
					cur = next;
					next = 0;
				}
			}
			if (flag) cout << k << " " << n << " NO" << endl;
			else cout << k << " " << n << " YES" << endl;
		}
	}
}