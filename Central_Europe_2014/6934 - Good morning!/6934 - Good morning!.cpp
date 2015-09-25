#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;


int keys[5][4] = {
		{ 1, 2, 3, -1 },
		{ 4, 5, 6, -1 },
		{ 7, 8, 9, -1 },
		{ -1, 0, -1, -1 },
		{ -1, -1, -1, -1 }
};

vector<int> v;

void bt(int row, int col, int n){
	if (keys[row][col] < 0) return;
	int cur = n;
	if (keys[row][col] == 0 && n == 0) return;
	while (cur <= 200){
		cur = cur*10 + keys[row][col];
		v.push_back(cur);
		bt(row + 1, col, n);
		bt(row + 1, col, cur);
		bt(row, col + 1, n);
		bt(row, col + 1, cur);
	}
}

int main(){
	bt(0, 0, 0);
	v.push_back(0);
	sort(v.begin(), v.end());
	int tc, num;
	cin >> tc;
	while (tc--){
		cin >> num;
		auto i = lower_bound(v.begin(), v.end(), num);
		int idx = i - v.begin();
		if (idx == v.size() - 1 || int(abs(num - v[idx]) <= int(abs(num - v[idx - 1])))){
			cout << v[idx] << endl;
		}
		else{
			cout << v[idx - 1] << endl;
		}
	}
}