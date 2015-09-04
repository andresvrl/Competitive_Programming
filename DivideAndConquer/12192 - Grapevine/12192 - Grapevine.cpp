#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

int main(){
	int n, m, q, l, u;
	int left, right, b_left, b_right, best;
	while (cin >> n >> m && (n || m)){
		vvi grid(n, vi(m));
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				cin >> grid[i][j];
			}
		}
		cin >> q;
		for (int t = 0; t < q; ++t){
			cin >> l >> u;
			best = 0;
			for (int i = 0; i < grid.size(); ++i){
				left = lower_bound(grid[i].begin(), grid[i].end(), l) - grid[i].begin();
				if (left == m) continue;
				for (int j = i; j < grid.size() && left < m; ++j, ++left){
					if (grid[j][left] <= u) best = max(best, j - i + 1);
					else break;
				}
			}
			cout << best << endl;
		}
		cout << "-" << endl;


	}
}