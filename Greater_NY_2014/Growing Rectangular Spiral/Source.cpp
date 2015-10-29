#include <iostream>
#include <vector>

using namespace std;

int main(){
	int p, c, x, y;
	cin >> p;
	while (p--){
		cin >> c >> x >> y;
		cout << c << " ";
		if (y > x) cout << 2 << " " << x << " " << y << endl;
		else{
			
			int b = x + 2;
			int c = b + 1;
			int a = c - y + 2;
			if (a < b && b < c){
				cout << 6 << " " << 1 << " " << 2 << " " << 3 << " ";
				cout << a << " " << b << " " << c << endl;
			}
			else{
				cout << "NO PATH" << endl;
			}
		}
	}
}