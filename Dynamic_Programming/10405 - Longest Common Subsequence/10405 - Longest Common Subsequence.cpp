#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stdio.h>

using namespace std;
typedef vector<int> vi;

char X[1005], Y[1005];
int m[1005][1005];

int LCS(int i, int j){
	if (i < 0 || j < 0) return 0;
	if (m[i][j] != -1) return m[i][j];
	if (X[i] == Y[j])
		return m[i][j] = 1 + LCS(i - 1, j - 1);
	return m[i][j] = max(LCS(i - 1, j), LCS(i, j - 1));
}

int main(){
	while (gets(X) && gets(Y)){
		memset(m, -1, sizeof(m[0][0]) * 1005 * 1005);
		cout << LCS(strlen(X) - 1, strlen(Y) - 1) << endl;
	}
}