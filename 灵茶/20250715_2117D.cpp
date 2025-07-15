#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;


void solve() {
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int& v : arr) cin >> v;
	if (n == 1) {
		cout << "YES" << '\n';
		return;
	}
    int sum = arr[0] + arr[n-1];
	if (sum % (n + 1)) {
		cout << "NO" << '\n';
		return;
	}
	int d = sum / (n + 1);
	if (d > arr[0] || d > arr[n-1] || ((arr[0] - d) % (n - 1)) || ((arr[n-1] - d) % (n - 1))) {
		cout << "NO" << '\n';
		return;
	}
	int b = (arr[0] - d) / (n - 1), a = (arr[n-1] - d) / (n - 1);
    for (int i = 1; i <= n; ++i) {
        if (i * a + (n + 1 - i) * b != arr[i-1]) {
            cout << "NO" << '\n';
            return;
        }
    }
	cout << "YES" << '\n';
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}