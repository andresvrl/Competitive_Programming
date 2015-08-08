#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	int t, n;
	string s;
	cin >> t;
	for (int case_ = 1; case_ <= t; ++case_) {
		cin >> n;
		cin >> s;
		int scarecrows = 0;
		for (int i = 1; i < s.size() - 1; ++i) {
			if (s[i - 1] == '.') {
				s[i - 1] = '#';
				s[i] = '#';
				s[i + 1] = '#';
				scarecrows++;
			}
		}
		if (s[s.size() - 1] == '.' || s[s.size() - 2] == '.')
			scarecrows++;
		cout << "Case " << case_ << ": " << scarecrows << endl;
	}
}
