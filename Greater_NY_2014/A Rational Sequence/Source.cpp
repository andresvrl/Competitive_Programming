#include <iostream>
using namespace std;

int main(){
	int k, fa, fb, t;
	char c;
	cin >> k;
	while (k--){
		cin >> t;
		cout << t << " ";
		cin >> fa >> c >> fb;
		int left = 0, right = 0;
		if (fa >= fb){
			if (fb == 1){
				cout << 1 << "/" << fa + 1 << endl;
			}
			else{
				while (fa > fb){
					fa -= fb;
					right++;
				}
				fb -= fa;
				fa += fb;
				for (int i = 0; i < right; i++){
					fb += fa;
				}
				cout << fa << "/" << fb << endl;
			}
		}
		else{
			int pa = fa;
			int pb = fb - fa;
			cout << (pa + pb) << "/" << pb << endl;
		}
	}
}