#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
typedef pair<int, int> ii;
typedef pair<int, ii> edge;
typedef vector<int> vi;
const int INF = 1000000000;

int main(){
	int n, m, si, ni, ki;
	int u, v, w;
	string oi;
	while (cin >> n && n){
		cin >> m;
		vector<edge> edgelist; 
		for (int i = 0; i < n + 1; ++i){
			edgelist.push_back(edge(n + 1, ii(i, 0)));
		}
		for (int i = 0; i < m; ++i){
			cin >> si >> ni >> oi >> ki;
			// si...si+n = s0...si+n - s0...si-1
			ni += si;
			si--;
			if (oi == "gt")
				edgelist.push_back(edge(ni, ii(si, -ki - 1))); 
			else //since we deal with integers, a < b -> a <= b - 1 
				edgelist.push_back(edge(si, ii(ni, ki - 1)));
		}
		
		//bellman ford
		bool flag = true;
		vi dist(n + 2, 1000000000); dist[n + 1] = 0;
		for (int i = 0; i <= n && flag; ++i){
			flag = false;
			for (int j = 0; j < edgelist.size(); ++j){
				u = edgelist[j].first;
				v = edgelist[j].second.first;
				w = edgelist[j].second.second;
				if (dist[v] > dist[u] + w){
					dist[v] = dist[u] + w;
					flag = true;
				}
			}
		}

		bool cycle = false;
		for (int j = 0; j < edgelist.size(); ++j){
			u = edgelist[j].first;
			v = edgelist[j].second.first;
			w = edgelist[j].second.second;
			if (dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
				cycle = true;
			}
		}

		if (cycle) cout << "successful conspiracy" << endl;
		else cout << "lamentable kingdom" << endl;
	}
}