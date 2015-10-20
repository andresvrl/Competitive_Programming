#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
	ll tmp;
	while (b){ a %= b; tmp = a; a = b; b = tmp; }
	return a;
}

ll lcm(ll a, ll b) {
	return a / gcd(a, b)*b;
}

ll mod(ll a, ll b) {
	return ((a%b) + b) % b;
}

struct fraction{
	ll n;
	ll d;
};

fraction simplify(fraction c){
	ll g = gcd(c.n, c.d);
	c.n /= g;
	c.d /= g;
	return c;
}

fraction mult(fraction a, fraction b){
	fraction c;
	c.n = a.n * b.n;
	c.d = a.d * b.d;
	return c;
}

fraction div(fraction a, fraction b){
	fraction c;
	c.n = a.n * b.d;
	c.d = a.d * b.n;
	return c;
}

fraction add(fraction a, fraction b){
	ll l = lcm(a.d, b.d);
	fraction c;
	c.n = (a.n * (l / a.d)) + (b.n * (l / b.d));
	c.d = l;
	return c;
}

fraction sub(fraction a, fraction b){
	ll l = lcm(a.d, b.d);
	fraction c;
	c.n = (a.n * (l / a.d)) - (b.n * (l / b.d));
	c.d = l;
	return c;
}

fraction cont_to_frac(vector<ll> cont){
	vector<ll> v(cont.size() + 1);
	v[cont.size()] = 1;
	v[cont.size() - 1] = cont[cont.size() - 1];
	for (ll i = cont.size() - 2; i >= 0; i--){
		v[i] = v[i + 1] * cont[i] + v[i + 2];
	}
	fraction c;
	c.n = v[0];
	c.d = v[1];
	return c;
}

vector<ll> frac_to_cont(fraction f){
	vector<ll> v;
	ll tmp;
	while (f.d != 0){
		v.push_back(f.n / f.d);
		tmp = f.n;
		f.n = f.d;
		f.d = mod(tmp, f.n);
	}
	return v;
}

void printc(vector<ll> c){
	for (ll i = 0; i < c.size() - 1; i++) cout << c[i] << " ";
	cout << c[c.size() - 1] << endl;
}

void printfr(fraction f){
	cout << f.n << " / " << f.d << endl;
}

int main(){
	ll n1, n2;
	ll tc = 1;
	while (cin >> n1 >> n2){
		vector<ll> c1(n1), c2(n2);
		for (ll i = 0; i < n1; i++) cin >> c1[i];
		for (ll i = 0; i < n2; i++) cin >> c2[i];

		fraction f1 = cont_to_frac(c1);
		fraction f2 = cont_to_frac(c2);
		//printfr(f1);
		//printfr(f2);
		cout << "Case " << tc++ << ":" << endl;
		fraction a = add(f1, f2);
		fraction b = sub(f1, f2);
		fraction c = mult(f1, f2);
		fraction d = div(f1, f2);

		printc(frac_to_cont(simplify(a)));
		printc(frac_to_cont(simplify(b)));
		printc(frac_to_cont(simplify(c)));
		printc(frac_to_cont(simplify(d)));
	}
}