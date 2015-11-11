#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

vvi g;

bool dp[1005][1005];
int dpnum[1005][1005];
int tc;

bool isDisjoint(int i, int j){
	if (i == 1 || j == 1) return true;
	if (i == j) return false;
	if (dpnum[i][j] == tc) return dp[i][j];
	bool ans = false;
	if (j < i) swap(i, j);
	for (auto &p : g[j]) ans = ans || isDisjoint(i, p);
	dpnum[i][j] = tc;
	return dp[i][j] = ans;
}

int main(int argc, char* argv[])
{
	int n, p;
	while (cin >> n >> p){
		tc++;
		g = vvi(n + 1, vi());
		int a, b;
		for (int i = 0; i < p; i++){
			cin >> a >> b;
			g[b].push_back(a);
		}
		int ans = n - 1;
		for (int i = 2; i < n; i++)
			for (int j = i + 1; j <= n; j++)
				ans += isDisjoint(i, j);

		cout << ans << endl;
	}

	return 0;
}