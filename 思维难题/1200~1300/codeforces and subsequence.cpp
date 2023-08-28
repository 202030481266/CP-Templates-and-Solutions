#include <bits/stdc++.h>
using namespace std;


// 简单构造即可，一个一个加一直到组合数大于n


void solve() {
	unsigned long long n;
	cin >> n;

	vector<int> cnt(10, 1);
	unsigned long long res = 1;
	int a = 0;
	while (res < n) {
		res = res / cnt[a] * (++cnt[a]);
		a = (a + 1) % 10;
	}

	string ex = "codeforces";
	string ans;
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < cnt[i]; ++j)
			ans += ex[i];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T = 1;
	while (T--) {
		solve();
	}
}