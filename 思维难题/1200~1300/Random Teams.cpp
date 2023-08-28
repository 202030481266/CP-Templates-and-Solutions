#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

ull binomial(int n, int k) {
    ull res = 1;
    for (int i = 0; i < k; i++) {
        res = res * (n - i) / (i + 1);
    }
    return res;
}

// 平均分配最小，最大分配应该尽可能多
// 特殊到一般的技巧

void solve() {
	int n, m;
	cin >> n >> m;
	ull km, kx;
	ull x = (n / m), y = (n % m);
	km = y * binomial(x + 1, 2) + (m - y) * binomial(x, 2);
	kx = binomial(n - m + 1, 2);
	cout << km << ' ' << kx << endl;
}

int main() {
	solve();
}