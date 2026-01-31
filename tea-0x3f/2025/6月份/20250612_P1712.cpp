// https://www.luogu.com.cn/problem/P1712
// 超时 二分答案 + 线段树
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 5e5 + 7;

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int n, m, N;
int a[maxn];
int see[maxn << 2], lazy[maxn << 2], mx[maxn << 2], have[maxn];

void pushup(int rt) {
	mx[rt] = max(mx[ls], mx[rs]);
}

void pushdown(int rt) {
	if (lazy[rt]) {
		lazy[ls] += lazy[rt];
		lazy[rs] += lazy[rt];
		see[ls] += lazy[rt];
		see[rs] += lazy[rt];
		if (mx[ls]) mx[ls] += lazy[rt];
		if (mx[rs]) mx[rs] += lazy[rt];
		lazy[rt] = 0;
	}
}

void build(int rt, int l, int r) {
	see[rt] = lazy[rt] = mx[rt] = 0;
	if (l == r) {
		have[l] = 0;
		return;
	}
	build(lson);
	build(rson);
}

void modify(int rt, int l, int r, int p, int val) { // 单点存在值和see修改
	if (l == r) {
		have[l] += val;
		see[rt] += val;
		if (have[l] > 0) mx[rt] = see[rt]; // 只有存在才能看到
		else mx[rt] = 0;
        return;
	}
	pushdown(rt);
	if (p <= mid) modify(lson, p, val);
	else modify(rson, p, val);
	pushup(rt);
}


void update(int rt, int l, int r, int L, int R, int val) { // 区间的see加上1
	if (L <= l && r <= R) {
		see[rt] += val;
		lazy[rt] += val;
		if (mx[rt]) mx[rt] += val; // 如果存在数字的话，那么最起码也是1
		return;
	}
	pushdown(rt);
	if (R <= mid) update(lson, L, R, val);
	else if (L > mid) update(rson, L, R, val);
	else {
		update(lson, L, mid, val);
		update(rson, mid + 1, R, val);
	}
	pushup(rt);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	vector<array<int, 3>> a(n);
	vector<array<int, 3>> events;
	vector<int> b(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i][0] >> a[i][1];
		b[i] = a[i][1] - a[i][0];
		a[i][2] = b[i];
	}
	if (m == 1) {
		cout << 0 << '\n';
		return 0;
	}
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	N = b.size() + 1;
	for (auto& e : a) {
		events.push_back({ e[0], 1, e[2]});
		events.push_back({ e[1] + 1, -1, e[2]});
	}
	sort(events.begin(), events.end());
	int mx_val = 0;
	int p = 0, flag = 0;
	n = events.size();
	while (p < n) {
		int i = p + 1;
		while (i < n && events[i][0] == events[p][0]) ++i;
		for (int k = p; k < i; ++k) {
			mx_val += events[k][1];
		}
		if (mx_val >= m) {
			flag = 1;
			break;
		}
		p = i;
	}
	if (!flag) {
		cout << -1 << '\n';
		return 0;
	}
	auto check = [&](int len) -> bool {
		build(1, 1, N);
		int i = 0;
		while (i < n) {
			int j = i + 1;
			while (j < n && events[j][0] == events[i][0]) ++j;
			for (int k = i, L, R, pos; k < j; ++k) {
				pos = lower_bound(b.begin(), b.end(), events[k][2]) - b.begin() + 1;
				modify(1, 1, N, pos, events[k][1]);
				R = upper_bound(b.begin(), b.end(), events[k][2] + len) - b.begin() + 1;
				L = pos + 1;
				if (R - 1 >= L) update(1, 1, N, L, R - 1, events[k][1]);
			}
			if (mx[1] >= m) return true;
			i = j;
		}
		return false;
	};

	int vl = 0, vr = b.back() - b[0] + 1;
	while (vl + 1 < vr) {
		int vmid = (vl + vr) >> 1;
		if (check(vmid)) vr = vmid;
		else vl = vmid;
	}

	cout << vr << '\n';
	return 0;
}

// 滑动窗口优化二分答案！首先按照长度排序，然后线段下标作为线段树维护
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 1e6 + 7;

int n, m;
int lazy[maxn << 2], mx[maxn << 2];

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

void pushup(int rt) {
	mx[rt] = max(mx[ls], mx[rs]);
}

void pushdown(int rt) {
	if (lazy[rt]) {
		lazy[ls] += lazy[rt];
		lazy[rs] += lazy[rt];
		mx[ls] += lazy[rt];
		mx[rs] += lazy[rt];
		lazy[rt] = 0;
	}
}

void update(int rt, int l, int r, int L, int R, int val) {
	if (L <= l && r <= R) {
		mx[rt] += val;
		lazy[rt] += val;
		return;
	}
	pushdown(rt);
	if (R <= mid) update(lson, L, R, val);
	else if (L > mid) update(rson, L, R, val);
	else {
		update(lson, L, mid, val);
		update(rson, mid + 1, R, val);
	}
	pushup(rt);
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);
	cin >> n >> m;
	vector<array<int, 3>> a(n);
	vector<int> b;
	for (int i = 0; i < n; ++i) {
		cin >> a[i][0] >> a[i][1];
		a[i][2] = a[i][1] - a[i][0];
		b.emplace_back(a[i][0]);
		b.emplace_back(a[i][1]);
	}
	if (m == 1) {
		cout << 0 << '\n';
		return 0;
	}
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	sort(a.begin(), a.end(), [&](const auto& x, const auto& y) {
		return x[2] < y[2];
		});
	int l = 0, ans = inf, N = b.size();
	for (int i = 0, L, R; i < n; ++i) {
		L = lower_bound(b.begin(), b.end(), a[i][0]) - b.begin() + 1;
		R = lower_bound(b.begin(), b.end(), a[i][1]) - b.begin() + 1;
		// [L, R]
		update(1, 1, N, L, R, 1);
		while (mx[1] >= m) {
			ans = min(ans, a[i][2] - a[l][2]);
			L = lower_bound(b.begin(), b.end(), a[l][0]) - b.begin() + 1;
			R = lower_bound(b.begin(), b.end(), a[l][1]) - b.begin() + 1;
			update(1, 1, N, L, R, -1);
			l++;
		}
	}
	if (ans == inf) cout << -1 << '\n';
	else cout << ans << '\n';
}