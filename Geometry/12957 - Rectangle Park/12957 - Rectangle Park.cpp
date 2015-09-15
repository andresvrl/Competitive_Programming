#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> ii;

int main(){
	int n, x, y;
	while (cin >> n){
		vector<ii> p;
		for (int i = 0; i < n; ++i){
			cin >> x >> y;
			p.push_back(ii(x, y));
		}
		sort(p.begin(), p.end());
		
		int count = 0;
		int miny = 1000000000;
		int maxy = -1000000000;
		for (int i = 0; i < n; ++i){
			miny = 1000000000;
			maxy = -1000000000;
			for (int j = i + 1; j < n; ++j){
				if (p[j].second > p[i].second && p[j].second < miny){
					miny = p[j].second; 
					++count;
				}
				else if (p[j].second < p[i].second && p[j].second > maxy){
					maxy = p[j].second;
					++count;
				}
			}
		}
		cout << count << endl;
	}
}
