#include <iostream>

using namespace std;

long long D[31];
long long A[31];

int n;

int main(){
	D[0] = 1;
	A[1] = 1;
	for (int i = 2; i < 31; ++i){
		if (i % 2 == 0)
			D[i] = D[i - 2] + 2 * A[i - 1];
		else
			A[i] = D[i - 1] + A[i - 2];
	}
	while (cin >> n && (n != -1)){
		if (n % 2 == 1) cout << 0 << endl;
		else cout << D[n] << endl;
	}
}