#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct node{
	node *left, *right;
	int data;
	node(int d){ data = d; right = nullptr; left = nullptr; };
};

vector<int> preord;

void insert(node *&root, int data){
	if (root == nullptr){
		root = new node(data);
		return;
	}
	if (data <= root->data) insert(root->left, data);
	else insert(root->right, data);
}

void preorder(node *&root){
	if (root == nullptr) return;
	preord.push_back(root->data);
	preorder(root->left);
	preorder(root->right);
}

int main(){
	int n;
	int tc = 1;
	while (cin >> n){
		preord.clear();
		vector<int> bt;
		bt.push_back(n);
		node *root = new node(n);
		while (cin >> n && n >= 0){
			bt.push_back(n);
			insert(root, n);
		}

		preorder(root);
		bool bst = true;
		for (int i = 0; i < preord.size(); i++){
			if (preord[i] != bt[i]) bst = false;
		}
		cout << "Case " << tc++ << ": ";
		if (bst) cout << "yes" << endl;
		else cout << "no" << endl;
	}
}