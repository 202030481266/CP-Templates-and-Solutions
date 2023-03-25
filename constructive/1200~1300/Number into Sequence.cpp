#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<long long, int> factorize(long long n) {
    map<long long, int> factors;
    for (int d = 2; (long long)d * d <= n; d++) {
        while (n % d == 0) {
            ++factors[d];
            n /= d;
        }
    }
    if (n > 1) {
        ++factors[n];
    }
    return factors;
}

void solve() {
	ll n;
	cin >> n;

	auto factors = factorize(n);
	int m_c = 0, m_f = 0;
	for (auto it : factors)
		if (it.second > m_c) m_c = it.second, m_f = it.first;
	cout << m_c << endl;
	if (m_c == 1) {
		cout << n << endl;
		return;
	}
	long long temp = n;
	for (int i = 1; i <= m_c - 1; ++i) {
		cout << m_f << ' ';
		temp /= m_f;
	}
	cout << temp << endl;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T = 1;
	cin >> T;
	while (T--)
		solve();
}
