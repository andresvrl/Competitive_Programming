#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;
typedef vector<int> vi;

int LDS(vi &arr){
	int n = arr.size();
	int m = 1;
	vi best(n, 1);
	for (int i = 1; i < n; ++i){
		for (int j = 0; j < i; ++j){
			if (arr[j] >= arr[i]){
				best[i] = max(best[i], best[j] + 1);
				m = max(m, best[i]);
			}
		}
	}
	return m;
}


int main(){
	int n;
	int Case = 1;
	while (1){
		cin >> n;
		if (n == -1) return 0;
		vi v;
		v.push_back(n);
		while (1){
			cin >> n;
			if (n == -1) break;
			v.push_back(n);
		}
		if (Case != 1) putchar('\n');
		printf("Test #%d:\n", Case++);
		printf("  maximum possible interceptions: %d\n", LDS(v));
	}
}