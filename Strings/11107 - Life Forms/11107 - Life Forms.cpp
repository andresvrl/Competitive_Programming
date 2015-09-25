#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <stdio.h>
using namespace std;

typedef pair<int, int> ii;

#define MAX_N 110000                         // second approach: O(n log n)
string T;                   // the input string, up to 100K characters
int n; //SET = T.length()!!!                // the length of input string
int RA[MAX_N], tempRA[MAX_N];        // rank array and temporary rank array
int SA[MAX_N], tempSA[MAX_N];    // suffix array and temporary suffix array
int c[MAX_N];                                    // for counting/radix sort
int owner[MAX_N];
int numlife;

void countingSort(int k) {                                          // O(n)
	int i, sum, maxi = max(300, n);   // up to 255 ASCII chars or length of n
	memset(c, 0, sizeof c);                          // clear frequency table
	for (i = 0; i < n; i++)       // count the frequency of each integer rank
		c[i + k < n ? RA[i + k] : 0]++;
	for (i = sum = 0; i < maxi; i++) {
		int t = c[i]; c[i] = sum; sum += t;
	}
	for (i = 0; i < n; i++)          // shuffle the suffix array if necessary
		tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
	for (i = 0; i < n; i++)                     // update the suffix array SA
		SA[i] = tempSA[i];
}

void constructSA() {         // this version can go up to 100000 characters
	int i, k, r;
	for (i = 0; i < n; i++) RA[i] = T[i];                 // initial rankings
	for (i = 0; i < n; i++) SA[i] = i;     // initial SA: {0, 1, 2, ..., n-1}
	for (k = 1; k < n; k <<= 1) {       // repeat sorting process log n times
		countingSort(k);  // actually radix sort: sort based on the second item
		countingSort(0);          // then (stable) sort based on the first item
		tempRA[SA[0]] = r = 0;             // re-ranking; start from rank r = 0
		for (i = 1; i < n; i++)                    // compare adjacent suffixes
			tempRA[SA[i]] = // if same pair => same rank r; otherwise, increase r
			(RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
		for (i = 0; i < n; i++)                     // update the rank array RA
			RA[i] = tempRA[i];
		if (RA[SA[n - 1]] == n - 1) break;               // nice optimization trick
	}
}


vector<ii> LCS() {                 // returns a vector of pair (the LCS length and its index)
	int idx = 0, maxLCP = 1, distinct = 0, len = 0;
	unordered_set<string> seen;
	vector<int> owner_count(numlife + 1, 0);
	vector<ii> res;
	for (int L = 1, R = 1; R < n; R++) {
		len = 0;
		if (++owner_count[owner[SA[R]]] == 1){
			distinct++;
		}
		if (distinct > numlife / 2){
			while (SA[R] + len < n && T[SA[L] + len] == T[SA[R] + len]) len++; //Brute force LCP calculation
			if (len < maxLCP || seen.count(T.substr(SA[R], len))){
				if (--owner_count[owner[SA[L++]]] == 0) distinct--;
				if (--owner_count[owner[SA[R--]]] == 0) distinct--;
			}
		}
		if (len > maxLCP){
			maxLCP = len;
			res.clear();
			res.push_back(ii(len, SA[R]));
			seen.insert(T.substr(SA[R], len));
		}
		else if (len == maxLCP && !seen.count(T.substr(SA[R], len))){
			res.push_back(ii(len, SA[R]));
			seen.insert(T.substr(SA[R], len));
		}
	}
	return res;
}

int main() {

	string s;
	bool first = true;
	while (cin >> numlife && numlife){
		if (first) first = false;
		else cout << endl;

		T.clear();
		n = 0;
		char offset = char(126) - 'z';
		char sep = 'a' + offset - 1;
		for (int i = 0; i < numlife; ++i){
			cin >> s;
			for (auto &ch : s) ch += offset;
			s += sep--;
			fill(owner + n, owner + n + s.size(), i);
			T += s;
			n += s.size();
		}

		if (numlife == 1){
			for (auto &ch : s) ch -= offset;
			cout << s.substr(0, s.size() - 1) << endl;
			continue;
		}

		constructSA();
		vector<ii> ans = LCS();

		if (ans.size() == 0) cout << "?" << endl;
		else{
			for (int i = 0; i < ans.size(); i++){
				s = T.substr(ans[i].second, ans[i].first);
				for (auto &ch : s) ch -= offset;
				cout << s << endl;
			}
		}
	}

	return 0;
}
