#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, tmp;
	cin >> n;
	while (n) {
		vector<int> ans;
		for (int i = 0; i < n; ++i) {
			cin >> tmp;
			if (tmp > 0) ans.push_back(tmp);
		}
		if (ans.size()) {
			for (int i = 0; i < ans.size() - 1; ++i)
				cout << ans[i] << ' ';
			cout << ans.back() << endl;
		}
		else
			cout << 0 << endl;
		cin >> n;
	}

}