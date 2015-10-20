#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main(){
	int n, s, tc = 1;
	while (cin >> n){
		unordered_map<int, int> j1;
		unordered_map<int, int> j2;
		vector<int> v1(n), v2(n);
		for (int i = 0; i < n; i++){
			cin >> s;
			v1[i] = s;
			j1[s] = i;
		}
		for (int i = 0; i < n; i++){
			cin >> s;
			v2[i] = s;
			j2[s] = i;
		}

		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
		int highest = -1;
		for (int i = n - 1, j = 1; i >= 0; i--, j++){
			if (j1[v1[i]] != j2[v2[i]]){
				highest = j;
				break;
			}
		}

		cout << "Case " << tc++ << ": ";
		if (highest == -1) cout << "agree" << endl;
		else cout << highest << endl;
	}
}