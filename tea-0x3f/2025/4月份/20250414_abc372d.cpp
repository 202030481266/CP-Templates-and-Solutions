#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int arr[200005];
int cnt[200005];
int r[200005];

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	stack<int> s;
	for (int i = n; i >= 1; --i) {
		while (!s.empty() && arr[s.top()] <= arr[i]) {
			r[s.top()] = i;
			s.pop();
		}
		s.push(i);
	}
	while (!s.empty()) {
		r[s.top()] = 0;
		s.pop();
	}
	for (int i = 1; i <= n; ++i) {
		// [r[i], i)
		cnt[r[i]]++;
		cnt[i]--;
	}
	int sum = cnt[0];
	for (int i = 1; i <= n; ++i) {
		sum += cnt[i];
		cout << sum << ' ';
	}
}