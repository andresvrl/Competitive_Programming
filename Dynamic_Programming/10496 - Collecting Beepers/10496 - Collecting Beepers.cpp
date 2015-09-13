#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdio.h>
using namespace std;
typedef pair<int, int> ii;

int all;
int am[15][15];
int dp[1 << 12][11];
int dp2[1 << 12][11];
int dpnum;
int tc, sizex, sizey, karelx, karely, numbeep, beepx, beepy;

int solve(int last, int state){
	if (state == all) return am[last][0];
	if (dp2[state][last] == dpnum) return dp[state][last];
	int best = 100000000;
	ii b;
	for (int i = 1; i < numbeep; ++i){
		if ((state & (1 << i)) == 0){
			best = min(best, solve(i, state | (1 << i)) + am[last][i]);
		}
	}
	dp2[state][last] = dpnum;
	return dp[state][last] = best;
}

int main(){
	cin >> tc;
	for(dpnum = 1; dpnum <= tc; ++dpnum){
		cin >> sizex >> sizey;
		cin >> karelx >> karely;
		cin >> numbeep;
		++numbeep;
		all = (1 << numbeep) - 1;
		vector<ii> points;
		points.push_back(ii(karelx, karely));
		for (int i = 1; i < numbeep; ++i){
			cin >> beepx >> beepy;
			points.push_back(ii(beepx, beepy));
		}
		for (int i = 0; i < points.size(); ++i){
			for (int j = 0; j < points.size(); ++j){
				am[i][j] = abs(points[i].first - points[j].first) 
							+ abs(points[i].second - points[j].second);
			}
		}
		cout << "The shortest path has length " << solve(0, 1) << endl;
	}
}