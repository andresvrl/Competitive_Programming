#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;
typedef vector<int> vi;

int main(){
	int tc, n, a, b;
	cin >> tc;
	for(int test = 1; test <= tc; ++test){
		cin >> n;
		vi h(n), w(n);
		for (int i = 0; i < n; ++i)
			cin >> h[i];
		for (int i = 0; i < n; ++i)
			cin >> w[i];
		vi dec(w), inc(w);
		int a = w[0], b = w[0];
		for (int i = 1; i < n; ++i){
			for (int j = 0; j < i; ++j){
				if (h[j] < h[i]){
					inc[i] = max(inc[i], w[i] + inc[j]);
				}
				else if(h[j] > h[i]){
					dec[i] = max(dec[i], w[i] + dec[j]);
				}
				a = max(inc[i], a);
				b = max(dec[i], b);
			}
		}
		if (a >= b)
			printf("Case %d. Increasing (%d). Decreasing (%d).\n", test, a, b);
		else
			printf("Case %d. Decreasing (%d). Increasing (%d).\n", test, b, a);
	}
}