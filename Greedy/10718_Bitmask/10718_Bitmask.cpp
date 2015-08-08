#include <iostream>
using namespace std;

int main() {
	unsigned n, l, u;
	while (cin >> n >> l >> u) {
		unsigned highbit = 1 << 31;
		unsigned ans = 0, tmp = 0;
		for (int i = 0; i < 32; ++i) {
			tmp = ans | highbit >> i;
			if (tmp <= l || (tmp <= u && !(n & highbit >> i)))
				ans = tmp;
		}
		cout << ans << endl;
	}
}
