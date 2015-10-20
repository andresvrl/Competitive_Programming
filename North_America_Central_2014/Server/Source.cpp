#include <iostream>
#include <vector>

using namespace std;

int main(){
	int n, t;
	int tc = 1;
	while (cin >> n >> t){
		int task, i, j;
		for (i = 0, j = 0; i < n; i++){
			cin >> task;
			t -= task;
			if (t >= 0) j++;
		}
		cout << "Case " << tc++ << ": " << j << endl;
	}
}