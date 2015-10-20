#include <algorithm>
#include <cstdio>
#include <cmath>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;
typedef pair<double, double> dd;
#define EPS 1e-9

struct line { double a, b, c; };          // a way to represent a line

// the answer is stored in the third parameter (pass by reference)
// ax + by + c = 0
void pointsToLine(dd p1, dd p2, line &l) {
	if (fabs(p1.first - p2.first) < EPS) {              // vertical line is fine
		l.a = 1.0;   l.b = 0.0;   l.c = -p1.first;           // default values
	}
	else {
		l.a = -(double)(p1.second - p2.second) / (p1.first - p2.first);
		l.b = 1.0;              // IMPORTANT: we fix the value of b to 1.0
		l.c = -(double)(l.a * p1.first) - p1.second;
	}
}

double getx(line l, double y){
	return ((l.b * y) + l.c) / (-1.0 * l.a);
}

double area(const vector<dd> &P) {
	double result = 0.0, x1, y1, x2, y2;
	for (int i = 0; i < (int)P.size() - 1; i++) {
		x1 = P[i].first; x2 = P[i + 1].first;
		y1 = P[i].second; y2 = P[i + 1].second;
		result += (x1 * y2 - x2 * y1);
	}
	return fabs(result) / 2.0;
}

template<typename P> struct cmp

{

	bool operator()(const P &p1, const P &p2)

	{

		if (p1.second < p2.second) return true;

		if (p1.second == p2.second) return p1.first > p2.first;

		return false;

	}

};

bool isLeft(dd a, dd b, dd c){
	return ((b.first - a.first)*(c.second - a.second) - (b.second - a.second)*(c.first - a.first)) > 0;
}

void prnt(dd p){
	cout << p.first << " " << p.second << endl;
}

int main(){
	int n;
	double b, l;
	double x, y;
	int tc = 1;
	while (cin >> n){
		cin >> b >> l;
		l /= b;
		l *= 1000;
		vector<dd> p(n);
		dd topleft(-10000, -10000), topright(-10000, -10000), bottomleft(-10000, -10000), bottomright(-10000, -10000);
		double curmax = -1;
		for (int i = 0; i < n; i++){
			cin >> x >> y;
			p[i] = dd(x, y);
			if (y == 0){
				if (bottomleft.first == -10000 || bottomleft.first > x){
					bottomleft = dd(x, y);
				}
				if (bottomright.first == -10000 || bottomright.first < x){
					bottomright = dd(x, y);
				}
			}
			if (y >= curmax){
				curmax = y;
				if (topleft.first == -10000 || topleft.second < y){
					topleft = dd(x, y);
				}
				else if (topleft.first > x && topleft.second == y){
					topleft = dd(x, y);
				}
				if (topright.first == -10000 || topright.second < y){
					topright = dd(x, y);
				}
				else if (topright.first < x && topright.second == y){
					topright = dd(x, y);
				}
			}
		}
		//prnt(topleft);
		//prnt(topright);
		//prnt(bottomleft);
		//prnt(bottomright);
		dd p1 = dd((bottomleft.first + bottomright.first) / 2, 0);
		dd p2 = dd((topleft.first + topright.first) / 2, curmax);
		vector<dd> left, right;
		for (int i = 0; i < p.size(); i++){
			if (isLeft(p1, p2, p[i]))
				left.push_back(p[i]);
			else right.push_back(p[i]);
		}
		sort(left.begin(), left.end(), cmp<dd>());
		sort(right.begin(), right.end(), cmp<dd>());
		//for (auto i : left) cout << i.first << " " << i.second << " | ";
		//cout << endl; for (auto i : right) cout << i.first << " " << i.second << " | ";
		vector<dd> all(left);
		for (int i = right.size() - 1; i >= 0; i--) all.push_back(right[i]);
		double area_ = area(all);
		double low = 0, high = curmax;
		double mid = high;
		if (l >= area_){
			printf("Case %d: %.4f\n", tc++, mid);
			continue;
		}
		while (fabs(area_ - l) > EPS){
			//cout << area_ << endl;
			//cout << l << endl;
			//cout << mid << endl;
			mid = (low + high) / 2;
			vector<dd> curleft, curright;
			curleft.push_back(left[0]);
			curright.push_back(right[0]);
			for (int i = 1; i < left.size(); i++){
				if (left[i].second < mid){
					curleft.push_back(left[i]);
				}
				else{
					line lin;
					pointsToLine(left[i - 1], left[i], lin);
					curleft.push_back(dd(getx(lin, mid), mid));
					break;
				}
			}
			for (int i = 1; i < right.size(); i++){
				if (right[i].second < mid){
					curright.push_back(right[i]);
				}
				else{
					line lin;
					pointsToLine(right[i - 1], right[i], lin);
					curright.push_back(dd(getx(lin, mid), mid));
					break;
				}
			}
			vector<dd> both(curleft);
			for (int i = curright.size() - 1; i >= 0; i--) both.push_back(curright[i]);
			area_ = area(both);

			if (area_ > l){
				high = mid;
			}
			else{
				low = mid;
			}
			mid = (low + high) / 2;
		}
		printf("Case %d: %.4f\n", tc++, mid);
	}
}
