#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int inf = 0x3f3f3f3f;

int n, dis[maxn], pre[maxn];
array<int, 5> arr[maxn];
set<pii> s[maxn];

inline int lowbit(int i) {
	return i & -i;
}

void add(int p, pii val) {
	while (p <= n) {
		s[p].insert(val);
		p += lowbit(p);
	}
}

void del(int p, pii val) {
	while (p <= n) {
		s[p].erase(val);
		p += lowbit(p);
	}
}

vector<int> query(int p, pii val) {
	vector<int> res;
	while (p > 0) {
		auto upper_it = s[p].lower_bound(val);
		for (auto it = s[p].begin(); it != upper_it; ++it) { // < y + 1
			res.push_back(it->second);
		}
		p -= lowbit(p);
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> arr[i][0] >> arr[i][1] >> arr[i][2] >> arr[i][3];
		arr[i][4] = i;
	}
	sort(arr + 1, arr + 1 + n);
	for (int i = 1; i <= n; ++i) {
		add(i, { arr[i][1], i });
	}
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int u = q.front(), x = arr[u][2], y = arr[u][3];
		q.pop();
		int p = lower_bound(arr + 1, arr + 1 + n, array{ x + 1, -inf, -inf, -inf , -inf}) - arr;
		if (p > 1) {
			vector<int> nxt = query(p - 1, { y + 1, -inf }); // <= x
			for (int v : nxt) {
				pre[v] = u;
				dis[v] = dis[u] + 1;
				if (arr[v][4] == n) {
					cout << dis[v] << '\n';
					int cur = v;
					vector<int> ans;
					while (cur) {
						ans.push_back(arr[cur][4]);
						cur = pre[cur];
					}
					reverse(ans.begin(), ans.end());
					for (int m : ans) cout << m << ' ';
					return 0;
				}
				q.push(v);
			}
			for (int v : nxt) {
				del(v, { arr[v][1], v });
			}
		}
	}
	cout << -1 << '\n';
}