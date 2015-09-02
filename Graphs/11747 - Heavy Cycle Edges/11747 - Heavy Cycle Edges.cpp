#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> edge;
typedef vector<edge> ve;
typedef vector<int> vi;


class UnionFind {                                            
private:
	vi p, rank, setSize;                     
	int numSets;
public:
	UnionFind(int N) {
		setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
		p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i;
	}
	int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	void unionSet(int i, int j) {
		if (!isSameSet(i, j)) {
			numSets--;
			int x = findSet(i), y = findSet(j);
			if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
			else                   {
				p[x] = y; setSize[y] += setSize[x];
				if (rank[x] == rank[y]) rank[y]++;
			}
		}
	}
	int numDisjointSets() { return numSets; }
	int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

int main(){
	int n, m, u, v, w;
	while (cin >> n >> m && (n || m)){
		ve EdgeList;
		for (int i = 0; i < m; ++i){
			cin >> u >> v >> w;
			EdgeList.push_back(edge(w, ii(u, v)));
		}
		sort(EdgeList.begin(), EdgeList.end());

		UnionFind uf(n);
		vi h;
		for (auto &e : EdgeList){
			u = e.second.first; v = e.second.second; w = e.first;
			if (!uf.isSameSet(u, v)){
				uf.unionSet(u, v);
			}
			else{
				h.push_back(w);
			}
		}
		if (h.size() == 0) cout << "forest" << endl;
		else{
			sort(h.begin(), h.end());
			for (int i = 0; i < h.size() - 1; ++i){
				cout << h[i] << " ";
			}
			cout << h[h.size() - 1] << endl;
		}
	}
}