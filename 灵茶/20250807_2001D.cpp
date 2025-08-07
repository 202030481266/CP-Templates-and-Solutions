#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 300005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

int pos[maxn], a[maxn], b[maxn], c[maxn], use[maxn];

void solve() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		// 初始化
		pos[a[i]] = 0;
		use[a[i]] = 0;
		c[i] = 0;
		b[i] = 0;
	}
	b[n + 1] = 0;
	for (int i = n; i >= 1; --i) {
		b[i] = b[i + 1];
		if (!pos[a[i]]) {
			pos[a[i]] = i;
			++b[i];
		}
	}
	cout << b[1] << '\n';
	int flag = 1, k = 0, pre = 0;
	set<pii> mx, mn;
	for (int i = b[1]; i >= 1; --i) {
		while (k + 1 <= n) { // 闭区间写法比较好写
			if (b[k + 1] + c[k + 1] + c[k] >= i) {
				c[k + 1] += c[k];
				++k;
				if (!use[a[k]]) {
					mx.emplace(a[k], n - k);
					mn.emplace(a[k], k);
				}
			}
			else break;
		}
		if (flag) {
			while (!mx.empty()) {
				auto [val, idx] = *mx.rbegin();
				if (use[val] || n - idx < pre) {
					mx.erase(prev(mx.end()));
				}
				else break;
			}
			auto [val, idx] = *mx.rbegin();
			cout << val << (i == 1 ? '\n' : ' ');
			use[val] = 1;
			pre = n - idx;
			if (pos[val] > k) {
				c[k + 1]--;
				c[pos[val] + 1]++;
			}
		}
		else {
			while (!mn.empty()) {
				auto [val, idx] = *mn.begin();
				if (use[val] || idx < pre) {
					mn.erase(mn.begin());
				}
				else break;
			}
			auto [val, idx] = *mn.begin();
			cout << val << (i == 1 ? '\n' : ' ');
			use[val] = 1;
			pre = idx;
			if (pos[val] > k) {
				c[k + 1]--;
				c[pos[val] + 1]++;
			}
		}
		flag ^= 1;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}