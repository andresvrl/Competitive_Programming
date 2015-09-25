#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> primes;

bool comp[100000];

void cPrimes(){
	for (long long i = 2; i * i <= 1000000000; i++){
		if (!comp[i]){
			primes.push_back(i);
			for (long long j = i*i; j*j <= 1000000000; j += i){
				comp[i] = true;
			}
		}
	}
}

vector<long long> fact(long long a){
	vector<long long> r;
	long long pot = 1;
	while (a % 2 == 0){
		a /= 2;
		pot *= 2;
	}
	r.push_back(2 * pot);
	for (auto &i : primes){
		if (a == 1)break;
		if (a%i == 0){
			r.push_back(i);
			break;
		}
	}
	if (r.size() < 2 && a != 1){
		r.push_back(a);
	}
	sort(r.begin(), r.end());
	return r;
}

long long n;
void solve(){
	vector<long long> f = fact(n);
	long long a, b;
	if (2 <= f[0] && f[0] <= n){
		a = (f[0] * (f[0] - 1) + 2 * n) / (2 * f[0]);
		b = a - f[0] + 1;
		cout << n << " = " << b;
		b++;
		while (b <= a){
			cout << " + " << b++;
		}
		cout << endl;
	}
	else if (f.size()>1 && 2 <= f[1] && f[1] <= n) {
		a = (f[1] * (f[1] - 1) + 2 * n) / (2 * f[1]);
		b = a - f[1] + 1;
		cout << n << " = " << b;
		b++;
		while (b <= a){
			cout << " + " << b++;
		}
		cout << endl;
	}
	else {
		cout << "IMPOSSIBLE" << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cPrimes();
	int TC;
	cin >> TC;
	while (cin >> n){
		if (n == 1){
			cout << "IMPOSSIBLE" << endl;
			continue;
		}
		if (n % 2){
			cout << n << " = " << (n / 2) << " + " << (n / 2 + 1) << endl;
		}
		else {
			solve();
		}
	}

}