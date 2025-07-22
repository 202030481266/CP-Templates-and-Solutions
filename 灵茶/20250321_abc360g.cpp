#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 200005;

int n;
int arr[maxn], b[maxn], N;
int dp[maxn], g[maxn];

int getIdx(int val) {
	return lower_bound(b + 1, b + N + 1, val) - b;
}

int t1[maxn], t2[maxn];

inline int lowbit(int i) {
	return i & -i;
}

void update(int fenwick[], int val, int pos) {
	for (int i = val; i <= N; i += lowbit(i)) {
		if (dp[fenwick[i]] < dp[pos]) {
			fenwick[i] = pos;
		}
		else if (dp[fenwick[i]] == dp[pos] && g[pos] > g[fenwick[i]]) {
			fenwick[i] = pos;
		}
	}
}

int query(int fenwick[], int p) {
	int res = 0;
	for (int i = p; i; i -= lowbit(i)) {
		if (dp[fenwick[i]] > dp[res]) {
			res = fenwick[i];
		}
		else if (dp[fenwick[i]] == dp[res] && g[fenwick[i]] > g[res]) {
			res = fenwick[i];
		}
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	for (int i = 1; i <= n; ++i) b[i] = arr[i];
	sort(b + 1, b + 1 + n);
	N = unique(b + 1, b + 1 + n) - b - 1;
	int mx_len = 0;
	for (int i = 1; i <= n; ++i) {
		int idx = getIdx(arr[i]);
		int mx_pre = query(t1, idx - 1);
		dp[i] = dp[mx_pre] + 1;
		if (g[mx_pre]) g[i] = 1;
		else if (i > 1) {
			if (idx == 1) g[i] = 1;
			else {
				int x = -1;
				if (b[idx] - b[idx - 1] == 1) {
					x = query(t2, idx - 2);
				}
				else x = query(t2, idx - 1);
				if (x != -1 && dp[x] + 1 == dp[i]) g[i] = 1;
			}
		}
		update(t1, idx, i);
		if (i > 1) update(t2, getIdx(arr[i - 1]), i - 1);
		mx_len = max(mx_len, dp[i]);
	}
	for (int i = 1; i <= n; ++i) {
		if (dp[i] == mx_len && (g[i] || i < n)) {
			cout << mx_len + 1 << '\n';
			return 0;
		}
	}
	cout << mx_len << '\n';
}

