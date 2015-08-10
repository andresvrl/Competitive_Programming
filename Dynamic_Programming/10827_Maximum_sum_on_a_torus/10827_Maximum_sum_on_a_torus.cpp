#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, t;
	cin >> t;
	while (t--) {
		cin >> n;
		vector<vector<int> > vec(n, vector<int>(n));
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> vec[i][j];

		vector<int> recsum(n);
		int maxrec = -100000000;
		for (int i = 0; i < n; ++i) {
			fill(recsum.begin(), recsum.end(), 0);
			for (int j = i; j < n + i; ++j) {
				for (int k = 0; k < n; ++k) 
					recsum[k] += vec[j % n][k];

				for (int a = 0; a < n; ++a) {
					int maxloc = 0, maxglob = 0;
					for (int b = a; b < a + n; ++b) {
						maxloc = max(recsum[b % n], maxloc + recsum[b % n]);
						maxglob = max(maxglob, maxloc);
					}
					maxrec = max(maxglob, maxrec);
				}
			}
		}
		cout << maxrec << endl;
	}
}