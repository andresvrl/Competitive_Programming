#include <iostream>
#include <cstring>

using namespace std;

int visited[10005][105];
bool dp[10005][105];
int nums[10005];

int t, n, k;

int mod(int a, int b) {
	return ((a%b) + b) % b;
}

bool isDiv(int pos, int m) {
	if (pos >= n) return m == 0;
	if (visited[pos][m]) 
		return dp[pos][m];
	visited[pos][m] = true;
	return dp[pos][m] = isDiv(pos + 1, mod(m + nums[pos], k)) || isDiv(pos + 1, mod(m - nums[pos], k));
}

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> k;
		memset(dp, 0, sizeof(dp[0][0]) * 10005 * 105);
		memset(visited, 0, sizeof(visited[0][0]) * 10005 * 105);
		for (int i = 0; i < n; ++i)
			cin >> nums[i];
		if (isDiv(0, 0))
			cout << "Divisible" << endl;
		else
			cout << "Not divisible" << endl;
	}
}