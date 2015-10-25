#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int width(int len, int point){
	return (int)ceil(9.0 / 16.0 * len * point);
}

int p(int cw, int cm){
	return 8 + (int)ceil(40.0 * (cw - 4) / (cm - 4));
}

int main(){
	int w, n, c, tc = 1;
	string s;
	while (cin >> w >> n && w){
		int cm = 0;
		vector<pair<string, int>> v;
		for (int i = 0; i < n; i++){
			cin >> s >> c;
			cm = max(cm, c);
			v.push_back({ s, c });
		}
		int cur_row = w;
		int height = 0;
		int cur_height = 0;
		for (int i = 0; i < v.size(); i++){
			int len = v[i].first.size();
			int cw = v[i].second;
			int point = p(cw, cm);
			int wi = width(len, point);
			if (cur_row - wi >= 0){
				cur_row -= (wi + 10);
				cur_height = max(point, cur_height);
			}
			else{
				height += cur_height;
				cur_row = w - wi - 10;
				cur_height = point;
			}
		}
		height += cur_height;
		cout << "CLOUD " << tc++ << ": " << height << endl;
	}
}