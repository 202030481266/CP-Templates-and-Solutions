#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 5010;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

// 非常不好想的题目
int fenwick[maxn], n, pos[maxn], arr[maxn];

inline int lowbit(int i) {
	return i & -i;
}

void update(int p, int val) {
	while (p <= n) {
		fenwick[p] += val;
		p += lowbit(p);
	}
}

int query(int p) {
	int res = 0;
	while (p) {
		res += fenwick[p];
		p -= lowbit(p);
	}
	return res;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
		pos[arr[i]] = i;
		fenwick[i] = 0;
	}
	for (int i = 1; i <= n; ++i) update(i, 1);
	int ans = 0;
	for (int i = 1; i < n; ++i) {
		int p = pos[i];
		int left = query(p - 1), right = query(n) - query(p); 
		ans += min(left, right);
		update(p, -1);
	}
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve(); 
}