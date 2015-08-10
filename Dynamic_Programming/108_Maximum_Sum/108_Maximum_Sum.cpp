#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<vector<int> > vec(n, vector<int>(n));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> vec[i][j];

	vector<int> recsum(n);
	int maxrec = 0;
	for (int i = 0; i < n; ++i) {
		fill(recsum.begin(), recsum.end(), 0);
		for (int j = i; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				recsum[k] += vec[j][k];
			}
			int maxloc = 0, maxglob = 0;
			for (int a = 0; a < n; ++a) {
				maxloc = max(recsum[a], maxloc + recsum[a]);
				maxglob = max(maxglob, maxloc);
			}
			maxrec = max(maxglob, maxrec);
		}
	}
	cout << maxrec << endl;
}