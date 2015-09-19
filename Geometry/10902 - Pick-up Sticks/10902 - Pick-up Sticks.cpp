#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double EPS = 1e-12;

struct PT {
	double x, y;
	PT() {}
	PT(double x, double y) : x(x), y(y) {}
	PT(const PT &p) : x(p.x), y(p.y)    {}
	PT operator + (const PT &p)  const { return PT(x + p.x, y + p.y); }
	PT operator - (const PT &p)  const { return PT(x - p.x, y - p.y); }
	PT operator * (double c)     const { return PT(x*c, y*c); }
	PT operator / (double c)     const { return PT(x / c, y / c); }
};

double dot(PT p, PT q)     { return p.x*q.x + p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p - q, p - q); }
double cross(PT p, PT q)   { return p.x*q.y - p.y*q.x; }


// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) {
	return abs(cross(b - a, c - d)) < EPS;
}

bool LinesCollinear(PT a, PT b, PT c, PT d) {
	return LinesParallel(a, b, c, d)
		&& abs(cross(a - b, a - c)) < EPS
		&& abs(cross(c - d, c - a)) < EPS;
}


// determine if line segment from a to b intersects with 
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
	if (LinesCollinear(a, b, c, d)) {
		if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
			dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
		if (dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 && dot(c - b, d - b) > 0)
			return false;
		return true;
	}
	if (cross(d - a, b - a) * cross(c - a, b - a) > 0) return false;
	if (cross(a - c, d - c) * cross(b - c, d - c) > 0) return false;
	return true;
}
typedef pair < PT, PT> pp;

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	double a1, b1, a2, b2;
	while (cin >> n && n){
		vector<pp> p(n);
		for (int i = 0; i < n; ++i){
			cin >> a1 >> b1 >> a2 >> b2;
			p[i] = pp(PT(a1, b1), PT(a2, b2));
		}
		vector<int> t;
		bool flag = false;
		for (int i = n - 1; i >= 0; --i){
			flag = false;
			for (int j = i + 1; j < n; ++j){
				if (SegmentsIntersect(p[j].first, p[j].second, p[i].first, p[i].second)){
					flag = true;
					break;
				}
			}
			if (t.size() == 1000) break;
			if (!flag) t.push_back(i);
		}

		cout << "Top sticks: ";
		for (int i = t.size() - 1; i >= 1; --i){
			cout << t[i]+1 << ", ";
		} cout << t[0]+1 << "." << endl;
	}
}