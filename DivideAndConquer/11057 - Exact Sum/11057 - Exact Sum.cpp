#include <unordered_map>
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

int main(){
	int n, a, p, x, y, dif;
	while (cin >> n){
		unordered_map<int, int> um;
		for (int i = 0; i < n; ++i){
			cin >> a;
			um[a]++;
		}
		cin >> p;
		x = 0;
		y = 1000000000;
		for (auto &i : um){
			if (p - i.first < 0) continue;
			if (p - i.first == i.first && i.second > 1){
				x = i.first;
				y = i.first;
				break;
			}
			dif = p - i.first;
			if (um.count(dif) && abs(x-y) > abs(i.first - dif)){
				x = min(i.first, dif);
				y = max(i.first, dif);
			}
		}
		cout << "Peter should buy books whose prices are " << x << " and " << y << "." << endl << endl;
	}
}