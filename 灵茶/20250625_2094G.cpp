// https://codeforces.com/problemset/problem/2094/G
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int maxn = 200005;

int arr[maxn], pre[maxn], nxt[maxn], tot = 0;

int getNode(int val) {
	int c = ++tot;
	pre[c] = nxt[c] = c;
	arr[c] = val;
	return c;
}

int insert_before(int ptr, int val) {
	int c = getNode(val);
	int pre_e = pre[ptr];
	pre[c] = pre_e;
	nxt[c] = ptr;
	nxt[pre_e] = c;
	pre[ptr] = c;
	return c;
}

int insert_nxt(int ptr, int val) {
	int c = getNode(val);
	int nxt_e = nxt[ptr];
	pre[c] = ptr;
	nxt[c] = nxt_e;
	pre[nxt_e] = c;
	nxt[ptr] = c;
	return c;
}

void solve() {
	tot = 0;
	ll s1 = 0, s2 = 0, sum = 0, n = 0;
	int st = 0, ed = 0;
	int q, flag = 0;
	cin >> q;
	for (int i = 0, op, x; i < q; ++i) {
		cin >> op;
		if (op == 1) {
			s1 += sum - n * arr[ed];
			s2 += n * arr[ed] - sum;
			if (!flag) {
				st = pre[st];
				ed = pre[ed];
			}
			else {
				st = nxt[st];
				ed = nxt[ed];
			}
		}
		else if (op == 2) {
			flag ^= 1;
			swap(s1, s2);
			swap(st, ed);
		}
		else {
			cin >> x;
			++n;
			sum += x;
			s1 += x * n;
			s2 += sum;
			if (st == 0) {
				st = ed = getNode(x);
			}
			else {
				if (!flag) ed = insert_before(st, x);
				else ed = insert_nxt(st, x);
			}
		}
		cout << s1 << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 0;
	cin >> t;
	while (t--) {
		solve();
	}
}