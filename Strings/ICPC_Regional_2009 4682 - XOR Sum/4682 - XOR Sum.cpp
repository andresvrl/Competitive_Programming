#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Trie{
	Trie *t[2];
	Trie(){ t[0] = t[1] = nullptr; };
};

void insert(Trie *p, unsigned num, int pos = 31){
	if (pos < 0) return;
	bool child = num & (1 << pos);
	if (p->t[child] == nullptr){
		p->t[child] = new Trie();
	}
	insert(p->t[child], num, pos - 1);
}

unsigned maxi(Trie *p, unsigned num, unsigned so_far = 0, int pos = 31){
	if (pos < 0) return so_far;
	bool opo = !(num & (1 << pos));
	if (p->t[opo] != nullptr){
		return maxi(p->t[opo], num, so_far | (1 << pos), pos - 1);
	}
	else return maxi(p->t[!opo], num, so_far, pos - 1);
}

int main(){
	int tc, n;
	cin >> tc;
	while (tc--){
		cin >> n;
		vector<unsigned> v(n);
		for (int i = 0; i < n; i++) cin >> v[i];
		Trie root;
		unsigned pre = 0, m = 0;
		insert(&root, 0);
		for (auto &i : v){
			pre = pre ^ i;
			insert(&root, pre);
			m = max(m, maxi(&root, pre));
		}
		cout << m << endl;
	}
}