#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

ll in[14];
ll mini[14][14];
const ll INF = 1000000000;

int main(){
	int p, k;
	cin >> p;
	while (p--){
		cin >> k;
		for (int i = 1; i <= 12; i++) cin >> in[i];

		for (int i = 0; i < 14; i++) for (int j = 0; j < 14; j++) mini[i][j] = INF;

		for (int left = 1; left <= 12; left++){
			for (int right = left; right <= 12; right++){
				mini[left][right] = min(mini[left][right - 1], in[right]);
			}
		}

		ll ans = 0;

		for (int left = 1; left <= 12; left++){
			for (int right = left; right <= 12; right++){
				if (mini[left][right] > in[left - 1] && mini[left][right] > in[right + 1]) ans++;
			}
		}
		cout << k << " " << ans << endl;
		
	}
}