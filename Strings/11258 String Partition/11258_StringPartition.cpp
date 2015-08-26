#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

long long DP[300];
int DP2[300];

int c = 0;
string s;

int n;
long long limite = ((1LL << 31LL) - 1LL);

long long maximo(int inicio){
	if (inicio == n){
		return 0;
	}
	if (DP2[inicio] == c) return DP[inicio];
	DP2[inicio] = c;
	if (s[inicio] == '0') return DP[inicio] = maximo(inicio + 1);
	long long acumulado = 0;
	long long r = -1;
	for (int i = inicio; i < n; i++){
		acumulado = acumulado * 10 + s[i] - '0';
		if (acumulado <= limite){
			r = max(r, acumulado + maximo(i + 1));
		}
		else {
			break;
		}
	}
	return DP[inicio] = r;
}

int main()
{
	int TC;
	cin >> TC;
	while (TC--){
		c++;
		cin >> s;
		n = s.length();
		cout << maximo(0) << endl;
	}
}

