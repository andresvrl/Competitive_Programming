#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vi num, low, parent, ap;
int dfs_counter, rootchildren, root;
vvi AdjList;

void dfs(int p){
	num[p] = low[p] = dfs_counter++;
	for (auto &c : AdjList[p]){
		if (!num[c]){
			parent[c] = p;
			if (p == root)
				rootchildren++;
			dfs(c);
			if (low[c] >= num[p])
				ap[p] = 1;
			low[p] = min(low[p], low[c]);
		}
		else if (parent[p] != c){
			low[p] = min(low[p], num[c]);
		}
	}
}

int main() {

	int N;
	while (cin >> N && N){
		int A;
		AdjList.assign(N, vi());
		ap.assign(N, 0);
		num.assign(N, 0);
		low.assign(N, 1000000);
		parent.assign(N, -1);
		dfs_counter = 1;
		while (cin >> A && A){
			A--;
			cin.ignore();
			string linea;
			getline(cin, linea);
			stringstream ss;
			ss << linea;
			int v;
			while (ss >> v){
				v--;
				AdjList[A].push_back(v);
				AdjList[v].push_back(A);
			}
		}
		for (int i = 0; i < AdjList.size(); ++i){
			if (!num[i]){
				root = i;
				rootchildren = 0;
				dfs(i);
				ap[i] = (rootchildren > 1);
			}
		}
		int count = 0;
		for (int i = 0; i < ap.size(); ++i) {
			if (ap[i]) {
				++count;
			}
		}
		cout << count << endl;
	}
}