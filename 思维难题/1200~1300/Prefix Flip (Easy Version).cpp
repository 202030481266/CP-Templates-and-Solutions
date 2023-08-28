#include <bits/stdc++.h>
using namespace std;


void solve() {
	int n;
	cin >> n;

	string a, b;
	cin >> a >> b;

	int p = n - 1;
	vector<int> cnt;

	auto flip = [&](string x, int prefix) {
		string y = x;
		for (int i = 0; i <= prefix; ++i)
			x[i] = (x[i] == '0') ? '1' : '0';
		for (int i = 0; i <= prefix; ++i)
			y[i] = x[prefix - i];
		cnt.emplace_back(prefix + 1);
		return y;
	};

	while (p >= 0) {
		if (a[p] != b[p]) {
			// flip 0....p
			a = flip(a, p);
			if (a[p] != b[p]) {
				// flip the first value
				a = flip(a, 0);
				// flip 0..p
				a = flip(a, p);
			}
		}
		--p;
	}
	cout << cnt.size() << ' ';
	for (auto c : cnt) cout << c << ' ';
	cout << endl;
}


int main() {
	ios::sync_with_stdio(false);
	int T = 1;
	cin >> T;
	while (T--)
		solve();
}