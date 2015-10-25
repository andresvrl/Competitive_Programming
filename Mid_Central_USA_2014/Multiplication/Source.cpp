#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>


using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;

void printTop(const vi& a){
	printf("+-");
	for (int i = 0; i < a.size(); i++){
		printf("----");
	}
	printf("--+\n|");
	for (int i = 0; i < a.size(); i++){
		printf("   %d", a[i]);
	}
	printf("   |\n");
}

void printBottom(const vi &r, int start, bool first){
	if (!first){
		printf("|/ %d", r[start]);
	}
	else{
		printf("|  %d", r[start]);
	}
	for (int i = start + 1; i < r.size(); i++){
		printf(" / %d", r[i]);
	}
	printf("    |\n");

}

void printTable(const vector<vi> &t, const vi &a, const vi &b, const vi &r){
	printTop(a);
	int ms = 0;
	for (int i = 0; i < r.size(); i++){
		if (r[i] > 0){
			ms = i;
			break;
		}
	}
	for (int i = 0; i < t.size(); i++){
		printf("| +");
		for (int j = 0; j < t[i].size(); j++){
			printf("---+");
		}
		printf(" |\n");
		if (ms < i){
			printf("|/");
		}
		else{
			printf("| ");
		}
		for (int j = 0; j < t[i].size(); j++){
			printf("|%d /", t[i][j] / 10);
		}
		printf("| |\n| ");
		for (int j = 0; j < t[i].size(); j++){
			printf("| / ");
		}
		printf("|%d|\n", b[i]);
		if (ms <= i){
			printf("|%d", r[i]);
		}
		else{
			printf("| ");
		}
		for (int j = 0; j < t[i].size(); j++){
			printf("|/ %d", t[i][j] % 10);
		}
		printf("| |\n");
	}
	printf("| +");
	for (int j = 0; j < t[0].size(); j++){
		printf("---+");
	}
	printf(" |\n");

	printBottom(r, b.size(), ms == b.size());

	printf("+-");
	for (int i = 0; i < a.size(); i++){
		printf("----");
	}
	printf("--+\n");
}

int main(){
	int a, b;
	while (cin >> a >> b && (a || b)){
		vi va, vb;
		while (a){
			va.push_back(a % 10);
			a /= 10;
		}
		while (b){
			vb.push_back(b % 10);
			b /= 10;
		}

		reverse(va.begin(), va.end());
		reverse(vb.begin(), vb.end());

		int as = va.size(), bs = vb.size();

		vector<vi> table(vb.size(), vi());
		for (int i = 0; i < bs; i++){
			for (int j = 0; j < as; j++){
				table[i].push_back(vb[i] * va[j]);
			}
		}
		vi diag(as + bs, 0);
		

		for (int i = as - 1; i >= 0; i--){
			int sum = 0, row = bs - 1;
			sum += table[row][i] % 10;
			for (int col = i + 1; col < as && row >= 0; col++, row--){
				sum += table[row][col] / 10;
				if (row > 0) sum += table[row - 1][col] % 10;
			}
			diag[as - i - 1] += sum % 10;
			diag[as - i] += sum / 10;
		}
		for (int i = bs - 1; i >= 0; i--){
			int sum = 0, row = i, col = 0;
			sum += table[row][col] / 10;
			for (row--; row >= 0 &&  col < as; row--, col++){
				sum += table[row][col] % 10;
				if (col + 1 < as) sum += table[row][col + 1] / 10;
			}
			diag[as + bs - i - 1] += sum % 10;
			if (as + bs - i < diag.size()) diag[as + bs - i] += sum / 10;
		}
		for (int i = 0; i < diag.size(); i++){
			if (diag[i] >= 10){
				diag[i + 1] += diag[i] / 10;
				diag[i] %= 10;
			}
		}
		reverse(diag.begin(), diag.end());

		printTable(table, va, vb, diag);
	}
}