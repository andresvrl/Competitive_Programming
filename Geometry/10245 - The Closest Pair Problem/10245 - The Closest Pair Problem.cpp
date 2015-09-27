#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <stdio.h>

using namespace std;

typedef pair<double, double> dd;
#define x second
#define y first
const double eps = 1e-12;

double dist(dd a, dd b){
	return sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
}

bool cmp(dd a, dd b){
	return a.x < b.x;
}

int main(){
	int n;
	double a, b;
	while (cin >> n && n){
		vector<dd> xp;
		for (int i = 0; i < n; ++i){
			cin >> a >> b;
			xp.push_back(dd(b, a));
		}
		if (n < 2){
			printf("INFINITY\n");
			continue;
		}

		sort(xp.begin(), xp.end(), cmp);

		set<dd> yp;
		yp.insert(xp[0]);
		yp.insert(xp[1]);
		double min_dist = dist(xp[0], xp[1]);
		dd p;
		for (int left = 0, i = 2; i < n; ++i){
			p = xp[i];
			while (xp[left].x - p.x > min_dist && left < i){
				yp.erase(yp.find(xp[left++]));
			}
			auto low = yp.lower_bound(dd(p.y - min_dist, p.x - min_dist));
			while (low != yp.end() && p.y + min_dist >= low->y){
				min_dist = min(min_dist, dist(*low++, p));
			}
			yp.insert(p);
		}
		if (min_dist - eps < 10000.0)
			printf("%.4f\n", min_dist);
		else
			printf("INFINITY\n");
	}

}