#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<int> vi;


int main() {
	int n;
	cin >> n;
	while (n) {
		vector<int> vec(n);
		for (int i = 0; i < n; ++i) {
			cin >> vec[i];
		}

		int maxg = 0, maxl = 0;
		for (auto &i : vec) {
			maxl = max(0, maxl + i);
			maxg = max(maxg, maxl);
		}
		if (maxg == 0)
			cout << "Losing streak." << endl;
		else
			cout << "The maximum winning streak is " << maxg << "." << endl;
		cin >> n;
	}
}