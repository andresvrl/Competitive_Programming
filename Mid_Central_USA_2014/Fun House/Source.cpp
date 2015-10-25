#include <vector>
#include <string>
#include <iostream>


using namespace std;
typedef pair<int, int> ii;

			// right,	left,		down,		up
ii dir[4] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
enum di { RIGHT, LEFT, DOWN, UP };

int main(){
	int w, l;
	string s;
	int tc = 1;
	while (cin >> w >> l && w){
		vector<string> h;
		for (int i = 0; i < l; i++){
			cin >> s;
			h.push_back(s);
		}
		ii en;
		for (int i = 0; i < l; i++){
			for (int j = 0; j < w; j++){
				if (h[i][j] == '*'){
					en = ii(i, j);
					break;
				}
			}
		}
		int d;
		if (en.first == 0) d = DOWN;
		else if (en.first == l - 1) d = UP;
		else if (en.second == 0) d = RIGHT;
		else d = LEFT;

		while (1){
			do{
				en.first += dir[d].first;
				en.second += dir[d].second;
			} while (h[en.first][en.second] != '/' && h[en.first][en.second] != '\\' && h[en.first][en.second] != 'x');

			if (h[en.first][en.second] == 'x') break;
			if (h[en.first][en.second] == '/'){
				switch (d){
				case RIGHT:
					d = UP;
					break;
				case LEFT:
					d = DOWN;
					break;
				case UP:
					d = RIGHT;
					break;
				default:
					d = LEFT;
					break;
				}
			}
			else{
				switch (d){
				case RIGHT:
					d = DOWN;
					break;
				case LEFT:
					d = UP;
					break;
				case UP:
					d = LEFT;
					break;
				default:
					d = RIGHT;
					break;
				}
			}
		}

		h[en.first][en.second] = '&';
		cout << "HOUSE " << tc++ << endl;
		for (int i = 0; i < h.size(); i++){
			cout << h[i] << endl;
		}

	}
}