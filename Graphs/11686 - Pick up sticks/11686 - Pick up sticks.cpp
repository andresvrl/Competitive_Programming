#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector< vi > vvi;

#define UNVISITED 0
#define EXPLORED 1
#define VISITED 2

vi dfs_num;
vvi AdjList;

vi order;
bool possible;

void dfs(int u){
	if (dfs_num[u] == VISITED) return;
	if (dfs_num[u] == EXPLORED){
		possible = false;
		return;
	}
	dfs_num[u] = EXPLORED;
	for (int i = 0; i < AdjList[u].size(); i++){
		dfs(AdjList[u][i]);
	}
	order.push_back(u);
	dfs_num[u] = VISITED;
}

int main() {
	int V, E;
	while ((cin >> V >> E) && (V || E)){
		possible = true;
		order.clear();
		dfs_num.assign(V, 0);
		AdjList.assign(V, vi());
		for (int i = 0; i < E; i++){ 
			int A, B; 
			cin >> A >> B; 
			A--; B--;
			AdjList[A].push_back(B); 
		}

		for (int i = 0; i < V; i++){
			if (dfs_num[i] == UNVISITED){
				dfs(i);
			}
			if (!possible) break;
		}

		if (possible){

			for (int i = order.size() - 1; i >= 0; i--){
				cout << order[i]+1 << endl;
			}

		}
		else {
			cout << "IMPOSSIBLE" << endl;
		}


	}
}