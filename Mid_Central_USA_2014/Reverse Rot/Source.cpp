#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
	int n;
	string s;
	while (cin >> n && n){
		cin >> s;
		for (auto &i : s){
			if (i == '_') i = 'Z' + 1;
			if (i == '.') i = 'Z' + 2;
		}
		reverse(s.begin(), s.end());
		for (int i = 0, j = n; i < s.size(); i++, j = n){
			s[i] += n;
			if (s[i] > 'Z' + 2){
				s[i] = 'A' + (s[i] % ('Z'+2)) - 1;
			}
		}
		for (auto &i : s){
			if (i == 'Z' + 1) i = '_';
			if (i == 'Z' + 2) i = '.';
		}
		cout << s << endl;
	}
}