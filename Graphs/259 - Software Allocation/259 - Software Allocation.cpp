#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
using namespace std;

typedef vector<int> vi;

#define MAX_V 40
#define INF 1000000000

// once completes, if res[i][j] > 0, there is flow from j -> i
int res[MAX_V][MAX_V], source, target;
vi p;
vector<vi> AdjList;

int maxflow(){
	int mf = 0;
	while (1) {
		queue<int> q; q.push(source);
		p.assign(MAX_V, -1);
		while (!q.empty() && p[target] == -1) {
			int u = q.front(); q.pop();
			for (auto &v : AdjList[u]) {
				if (res[u][v] > 0 && p[v] == -1)
					q.push(v), p[v] = u;
			}
		}
		if (p[target] == -1) break;

		int flow = INF; // bottleneck
		for (int v = target; p[v] != -1; v = p[v]){
			flow = min(flow, res[p[v]][v]);
		}
		for (int v = target; p[v] != -1; v = p[v]){
			res[p[v]][v] -= flow;
			res[v][p[v]] += flow;
		}
		mf += flow;
	}
	return mf;
}

int main() {
	int app, num_app, pc, total;
	string s;
	source = 36;
	target = 37;

	while (getline(cin, s)){
		total = 0;
		memset(res, 0, sizeof(res));
		AdjList.assign(MAX_V, vi());
		for (int i = 26; i < 36; ++i){
			AdjList[i].push_back(target);
			AdjList[target].push_back(i);
			res[i][target] = 1;
		}
		do{
			app = s[0] - 'A';
			num_app = s[1] - '0';
			total += num_app;
			for (int i = 3;; i++){
				if (s[i] == ';') break;

				pc = s[i] - '0' + 26;
				res[app][pc] = 1;
				AdjList[app].push_back(pc);
				AdjList[pc].push_back(app);
			}

			res[source][app] = num_app;
			AdjList[source].push_back(app);

			getline(cin, s);
		} while (!s.empty());

		int mf = maxflow();

		if (mf < total) cout << "!" << endl;
		else{
			for (int i = 26; i < 36; ++i){
				bool flag = true;
				int j = 0;
				for (; j < 26; ++j){
					if (res[i][j]) break;
				}
				if (j < 26) cout << char(j + 'A');
				else cout << '_';
			}
			cout << endl;
		}

	}
}


