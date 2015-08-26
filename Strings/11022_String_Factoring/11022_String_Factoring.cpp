#include <iostream>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

map<string, int> dp;

int fac(string s){
	if (s.size() <= 1) return s.size();
	if (dp[s] != 0) return dp[s];
	else dp[s] = s.size();
	for (int i = 1; i < s.size(); ++i){
		for (int j = 2; i * j <= s.size(); ++j){
			if (s.substr(0, i) == s.substr(i*(j - 1), i))
				dp[s] = min(dp[s], fac(s.substr(0, i)) + fac(s.substr(i*j, string::npos)));
			else
				break;
		}
		dp[s] = min(dp[s], fac(s.substr(0, i)) + fac(s.substr(i, string::npos)));
	}
	return dp[s];
}

int main(){
	string s;
	cin >> s;
	while (s != "*"){
		dp.clear();
		cout << fac(s) << endl;
		cin >> s;
	}
}