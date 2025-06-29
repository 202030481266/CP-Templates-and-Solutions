#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
int a, b;
ull c;

int main() {
	cin >> a >> b >> c;
	int m = popcount(c);
	if (a + b < m || (a + b - m) & 1) {
		cout << -1 << '\n';
		return 0;
	}
	int x = (a + b - m) / 2, y = a - x;
    if (y < 0 || x > 60 - m || m - y < 0) {
        cout << -1 << endl;
        return 0;
    }
	ull v1 = 0, v2 = 0;
	for (int i = 0; i < 60; ++i) {
		if ((c >> i) & 1) {
			if (y) v1 |= (1ull << i), --y;
			else v2 |= (1ull << i);
		}
		else {
			if (x) {
				v1 |= (1ull << i);
				v2 |= (1ull << i);
				--x;
			}
		}
	}
	cout << v1 << ' ' << v2 << '\n';
}