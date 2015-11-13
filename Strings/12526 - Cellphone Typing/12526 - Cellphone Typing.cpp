#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
typedef pair<int, int> ii;

string s;

struct Trie{
	int n, m;
	bool fin;
	Trie *children[26];
	Trie(){
		for (int i = 0; i < 26; ++i) children[i] = nullptr;
		n = 0;
		m = 0;
		fin = false;
	}
};

void addWord(Trie *root, int cur){
	char c = s[cur] - 'a';
	if (root->children[c] == nullptr){
		root->children[c] = new Trie();
		root->n++;
	}
	root->children[c]->m++;
	if (cur < s.size() - 1) addWord(root->children[c], cur + 1);
	else root->children[c]->fin = true;
}

int dfs(Trie *root, char c){
	int ans = (!root->fin && root->n == 1) ? root->m : 0;
	for (int i = 0; i < 26; ++i){
		if (root->children[i] != nullptr){
			ans += dfs(root->children[i], 'a' + i);
		}
	}
	return ans;
}

int main(){
	int words;
	while (cin >> words){
		Trie root;
		long long total = 0;
		for (int i = 0; i < words; i++){
			cin >> s;
			total += s.length();
			addWord(&root, 0);
		}
		printf("%.2f\n",(total - dfs(&root, 'a')) / (double)words);
	}
}