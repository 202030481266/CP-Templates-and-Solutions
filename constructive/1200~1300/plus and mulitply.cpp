#include <bits/stdc++.h>
using namespace std;


void solve() {
	int n, a, b;
	cin >> n >> a >> b;

	// 无论怎么变换，开始的那个1始终都只会变成一个a的指数形式。
	// 因此对于所有集合里面的数字 m , 都有 m mod b = k is a power of a
	// 并且想要增加项就只能 + b which means that new number % b = a^k % b，想要改变 mod b的值就只能乘以a

	if (a == 1) {
		if ((n - 1) % b == 0) cout << "Yes" << endl;
		else cout << "No" << endl;
		return;
	}

	long long t = 1;
	bool flag = false;
	while (t <= n) {
		if (t % b == n % b)
			flag = true;
		t *= a;
	}
	cout << (flag ? "Yes" : "No") << endl;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T = 1;
	cin >> T;
	while (T--) solve();
}