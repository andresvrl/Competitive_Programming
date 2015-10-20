#include <iostream>
#include <string.h>

using namespace std;

typedef long long ll;

ll dp[50][50];

ll c(int n, int k){
	if (n == k || k == 0) return 1;
	if (dp[n][k] != 0) return dp[n][k];
	return dp[n][k] = c(n - 1, k - 1) + c(n - 1, k);
}

int main(){
	int n, k, tc;
	memset(dp, 0, sizeof dp);
	cin >> tc;
	for (int i = 1; i <= tc; i++){
		cin >> n >> k;
		cout << "Case " << i << ": " << c(n, k - 1) << endl;
	}
}