#include <iostream>
using namespace std;


int main() {
	long long n;
	int tc = 1;
	while (cin >> n){
		long long loops = 0, i = 1LL, j = 0;
		while (true){
			if (n >> i){
				loops += i * (1LL << j);
				i++;
				j++;
			}
			else{
				loops += i * (n - (1 << j) + 1);
				break;
			}
		}
		cout << "Case " << tc++ << " " << loops << endl;
	}
}
