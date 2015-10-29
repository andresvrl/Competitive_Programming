#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> vi;

int main(){
	vector<vi> all;
	all.push_back(vi({ 0 }));
	all.push_back(vi({ 1 }));
	for (int i = 2; i <= 2000; i++){
		vi &p = all[i - 1];
		int fz = -1;
		for (int j = 0; j < p.size(); j++){
			if (p[j] == 0){
				fz = j;
				break;
			}
		}
		
		if (fz == -1){
			int n = p.size();
			vi next(n + 1, 0);
			next[n] = n + 1;
			for (int j = n - 1; j >= 0; j--)
				next[j] = p[j] - 1;
			all.push_back(next);
		}
		else{
			vi next(p);
			next[fz] = fz + 1;
			for (int j = fz - 1; j >= 0; j--)
				next[j]--;
			all.push_back(next);
		}
	}

	int p, tc, n;
	cin >> p;
	while (p--){
		cin >> tc >> n;
		cout << tc << " " << all[n].size();
		for (int i = 0; i < all[n].size(); i++){
			if (i % 10 == 0) cout << endl << all[n][i];
			else cout << " " << all[n][i];
		}
		cout << endl;
	}
}