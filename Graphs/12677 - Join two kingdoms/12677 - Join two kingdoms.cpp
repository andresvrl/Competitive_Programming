#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdio.h>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

int getFar(int start, vvi &g, int &diam){
	vi dist(g.size(), 0);
	vi p(g.size(), -1);
	queue<int> q; q.push(start);
	int far = start;
	while (!q.empty()){
		int front = q.front(); q.pop();
		if (dist[front] > dist[far]) far = front;
		for (auto &u : g[front]){
			if (p[front] != u){
				p[u] = front;
				q.push(u);
				dist[u] = dist[front] + 1;
			}
		}
	}
	diam = dist[far];
	return far;
}

void fillDist(int start, vvi &g, vi &d){
	vi dist(g.size(), 0);
	vi p(g.size(), -1); 
	queue<int> q; q.push(start);
	int far = start;
	while (!q.empty()){
		int front = q.front(); q.pop();
		for (auto &u : g[front]){
			if (p[front] != u){
				p[u] = front;
				q.push(u);
				dist[u] = dist[front] + 1;
			}
		}
	}
	for (int i = 0; i < d.size(); i++) d[i] = max(d[i], dist[i]);
}

int main(){
	int n, q;
	while (cin >> n >> q){
		vvi nlog(n + 1, vi());
		vvi quad(q + 1, vi());
		int a, b;
		for (int i = 1; i < n; i++){
			cin >> a >> b;
			nlog[a].push_back(b);
			nlog[b].push_back(a);
		}
		for (int i = 1; i < q; i++){
			cin >> a >> b;
			quad[a].push_back(b);
			quad[b].push_back(a);
		}

		int ns, ne, nd;
		ns = getFar(1, nlog, nd);
		ne = getFar(ns, nlog, nd);

		int qs, qe, qd;
		qs = getFar(1, quad, qd);
		qe = getFar(qs, quad, qd);

		vi ndist(n + 1, 0);
		vi qdist(q + 1, 0);

		fillDist(ns, nlog, ndist);
		fillDist(ne, nlog, ndist);
		fillDist(qs, quad, qdist);
		fillDist(qe, quad, qdist);

		long long ans = 0;
		int diam = max(nd, qd);
		sort(qdist.begin(), qdist.end());
		vector<long long> sums(qdist.size(), 0);
		for (int i = 1; i < qdist.size(); i++) sums[i] = sums[i - 1] + qdist[i];

		for (int i = 1; i <= n; i++){
			auto lb = lower_bound(qdist.begin(), qdist.end(), diam - ndist[i] - 1);
			int num_smaller = max((int)(lb - qdist.begin()) - 1, 0);
			int num_greater = q - num_smaller;
			ans += num_smaller * diam;
			if (num_greater > 0)
				ans += sums.back() - sums[num_smaller] + (ndist[i] * num_greater) + num_greater;
		}
		printf("%.3f\n", ans / (double)(n * q));
	}
}