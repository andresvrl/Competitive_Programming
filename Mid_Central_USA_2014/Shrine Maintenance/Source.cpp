#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <stdio.h>

using namespace std;
int w, n, d, tmp;

bool solve(double cost, const vector<double> &dist){
	cost -= 2000;
	int d = dist.size();
	for (int s = 0; s < d; s++){
		int workers = 1;
		double work = 0;
		for (int i = 0; i < d - 1; i++){
			if (work + dist[(s + i) % dist.size() ] <= cost){
				work += dist[(s + i) % dist.size()];
			}
			else{
				workers++;
				work = 0;
			}
		}
		if (workers <= w) return true;
	}
	return false;
}

int main(){
	while (cin >> w >> n >> d && w){
		set<int> s;
		for (int i = 0; i < d; i++){
			cin >> tmp;
			s.insert(tmp);
			for (int j = 2; tmp * j <= n; j++)
				s.insert(tmp * j);
		}
		vector<int> shrines;
		for (auto &i : s) shrines.push_back(i);
		vector<double> dist(shrines.size());

		int si = shrines.size();
		dist[si - 1] = shrines[0] + n - shrines[si - 1];
		for (int i = 1; i < si; i++) dist[i - 1] = shrines[i] - shrines[i - 1];
		for (int i = 0; i < si; i++) dist[i] = 2000.0 * sin(dist[i] / n * acos(-1.0));

		double min_c = 2000.0, max_c = 2000.0 * acos(-1) * 8600;
		double mid = (min_c + max_c) / 2, oldmid = 0;

		while (fabs(mid - oldmid) > 0.001){
			if (solve(mid, dist)){
				max_c = mid;
			}
			else{
				min_c = mid;
			}
			oldmid = mid;
			mid = (min_c + max_c) / 2;
		}
		printf("%.1f\n", mid);
	}
}