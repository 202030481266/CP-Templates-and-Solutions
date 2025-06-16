// https://codeforces.com/problemset/problem/1076/A
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 2e5 + 7;

string s;
int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> s;
	int flag = 0;
	for (int i = 0; i < n - 1; ++i) {
		if (s[i] > s[i + 1]) {
			flag = 1;
			for (int j = 0; j < i; ++j) cout << s[j];
			for (int j = i + 1; j < n; ++j) cout << s[j];
			cout << endl;
			break;
		}
	}
	if (flag) return 0;
	cout << s.substr(0, n - 1) << endl;
}