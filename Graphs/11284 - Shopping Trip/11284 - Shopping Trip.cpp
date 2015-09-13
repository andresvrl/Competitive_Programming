#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <bitset>

using namespace std;
typedef vector<int> vi;
typedef long long ll;

const ll INF = 1000000000000;
int tc, stores, roads, from, to;
double weight;
int p;
int dpnum;

ll pdiff[51];
ll cost[15][15];
int dp[13][1 << 14];
int dp2[13][1 << 14];

ll AM[55][55];
vi destinations;

ll tsp(int last, int state){
	if (state == (1 << p) - 1) return cost[last][0];
	if (dp2[last][state] == dpnum) return dp[last][state];
	ll best = INF;
	for (int i = 1; i < p; ++i){
		if (!(state & (1 << i))){
			best = min(best, tsp(i, state | 1 << i) + cost[last][i] - pdiff[destinations[i]]);
		}
	}
	best = min(best, cost[last][0]);
	dp2[last][state] = dpnum;
	return dp[last][state] = best;
}

int main(){
	//ios_base::sync_with_stdio(false);
	cin >> tc;
	for(dpnum = 1; dpnum <= tc; ++dpnum){
		cin >> stores >> roads;
		for (int i = 0; i <= stores; ++i)
			for (int j = 0; j <= stores; ++j)
				AM[i][j] = INF;
		for (int i = 0; i <= stores; ++i) AM[i][i] = 0;

		for (int i = 0; i < roads; ++i){
			cin >> from >> to >> weight;
			AM[from][to] = min(ll(weight*100000.0), AM[from][to]);
			AM[to][from] = min(ll(weight*100000.0), AM[to][from]);
		}

		for (int k = 0; k <= stores; ++k)
			for (int i = 0; i <= stores; ++i)
				for (int j = 0; j <= stores; ++j)
					AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);

		destinations.clear();
		for (int i = 0; i <= stores; ++i) pdiff[i] = 0;
		cin >> p;
		destinations.push_back(0);
		for (int i = 0; i < p; ++i){
			cin >> to >> weight;
			if(pdiff[to] == 0.0) 
				destinations.push_back(to);
			pdiff[to] += ll(weight*100000.0);
		}
		p = destinations.size();

		for (int i = 0; i < p; ++i)
			for (int j = 0; j < p; ++j)
				cost[i][j] = AM[destinations[i]][destinations[j]];
		
		ll ans = -tsp(0, 1);
		if (ans <= 0) cout << "Don't leave the house" << endl;
		else printf("Daniel can save $%.2lf\n",ans/100000.0);
	}
}