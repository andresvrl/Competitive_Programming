#include <string>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;

unordered_set<string> dict;

bool dfs(string from, string &to){
	if (from == to) return true;
	bool can = false;
	string next;
	for (int i = 0; !can && i < from.size(); i++){
		next = from.substr(0, i) + from.substr(i + 1, string::npos);
		can = can || (dict.count(next) && dfs(next, to));
	}
	return can;
}

int main(){
	int tc = 1;
	int n, m;
	while (cin >> n){
		cout << "Case " << tc++ << ":" << endl;
		string s;
		dict.clear();
		for (int i = 0; i < n; i++){
			cin >> s;
			for (int i = 0; i < s.size(); i++){
				if (s[i] > 'Z') s[i] -= 32;
			}
			sort(s.begin(), s.end());
			dict.insert(s);
		}

		string s1, s2;
		cin >> m;
		for (int i = 0; i < m; i++){
			cin >> s1 >> s2;
			for (int i = 0; i < s1.size(); i++){
				if (s1[i] > 'Z') s1[i] -= 32;
			}
			for (int i = 0; i < s2.size(); i++){
				if (s2[i] > 'Z') s2[i] -= 32;
			}
			sort(s1.begin(), s1.end());
			sort(s2.begin(), s2.end());
			if (dict.count(s1) == 0 || dict.count(s2) == 0){
				cout << "no" << endl;
			}
			else{
				if (dfs(s2, s1)) cout << "yes" << endl;
				else cout << "no" << endl;
			}
		}
	}
}