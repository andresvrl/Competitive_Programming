#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

ll DP[50][50];

ll C(int n, int k){
	if (n < k || k < 0 || n < 0) return 0;
	if (n == 0 || n == k) return 1;
	if (DP[n][k]) return DP[n][k];
	return DP[n][k] = C(n - 1, k) + C(n - 1, k - 1);
}

int lista[20];

int main() {
	int n, k, c = 1;
	while (cin >> n && n){
		int m;
		int total = 0;
		for (int i = 0; i < n; i++){
			cin >> m;
			lista[i] = m;
			total += m;
		}
		cout << "Case " << c++ << ": ";
		if (total == 0){
			cout << 1 << endl;
		}
		else {
			ll r = 0;
			for (int i = 0; i < total; i++){
				r += C(n + i - 1, i);
			}
			for (int i = 0; i < n; i++){
				for (int j = 0; j < lista[i]; j++){
					r += C((n - i - 1) + (total - j) - 1, total - j);
				}
				total -= lista[i];
			}
			cout << r + 1 << endl;
		}
	}
}
