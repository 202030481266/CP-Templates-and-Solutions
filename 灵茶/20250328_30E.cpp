#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;

std::vector<int> z_function(std::string p) {
	std::vector<int> z(p.size());
	for (int i = 1, l = 0, r = 0; i < p.size(); ++i) {
		if (i <= r) z[i] = std::min(z[i - l], r - i + 1);
		while (i + z[i] < p.size() && p[i + z[i]] == p[z[i]]) ++z[i];
		if (i + z[i] - 1 > r) {
			r = i + z[i] - 1;
			l = i;
		}
	}
	z[0] = p.size();// 最后需要赋值一下
	return z;
}

std::vector<int> build_z_of_s(std::vector<int>& z, std::string s, std::string p) {
	std::vector<int> lcp(s.size());
	while (lcp[0] < s.size() && lcp[0] < p.size() && s[lcp[0]] == p[lcp[0]]) ++lcp[0];
	for (int i = 1, l = 0, r = lcp[0] - 1; i < s.size(); ++i) {
		if (i <= r) lcp[i] = std::min(z[i - l], r - i + 1);
		while (i + lcp[i] < s.size() && lcp[i] < p.size() && s[i + lcp[i]] == p[lcp[i]]) ++lcp[i];
		if (i + lcp[i] - 1 > r) {
			r = i + lcp[i] - 1;
			l = i;
		}
	}
	return lcp;
}

std::vector<int> odd_palindrome_radius(std::string s) {
	int n = s.size();
	vector<int> d1(s.size());
	for (int i = 0, l = 0, r = -1; i < n; ++i) {
		int k = (i > r ? 1 : min(d1[l + r - i], r - i + 1));
		while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) ++k;
		d1[i] = k--; // [0, k)
		if (i + k > r) {
			r = i + k;
			l = i - k;
		}
	}
	return d1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	string s;
	cin >> s;
	string p = s;
	reverse(p.begin(), p.end());
	auto pz = z_function(p);
	auto lcp = build_z_of_s(pz, s, p); // lcp[i] the max length of the common length between s[i] and p
	auto d = odd_palindrome_radius(s); // d[i] means the max palindrome radius length of s[i]
	int n = s.size(); // 可以证明答案中的mid一定是某一个位置为中心的最长回文子串
	vector<int> mx(n), mxp(n);
	vector events(n + 1, vector<int>{});
	vector<int> valid(n, 1);
	vector<int> que(n + 1);
	int st = 0, ed = 0;
	for (int i = 0; i < n; ++i) {
		events[lcp[i] + i].push_back(i);
	}
	int mx_pre = -1;
	for (int i = 0; i < n; ++i) {
		for (int pos : events[i]) {
			valid[pos] = 0;
			if (mx_pre == -1) mx_pre = pos;
			else if (lcp[pos] > lcp[mx_pre]) mx_pre = pos;
		}
		while (st < ed && !valid[que[st]]) ++st;
		if (mx_pre != -1) {
			mx[i] = lcp[mx_pre];
			mxp[i] = mx_pre;
		}
		if (st < ed && i - que[st] > mx[i]) {
			mx[i] = i - que[st]; // [que[st], i)
			mxp[i] = que[st];
		}
		que[ed++] = i;
	}
	int ans = 0;
	vector<pii> intervals;
	for (int i = 0; i < n; ++i) {
		// [i-d[i]+1, i+d[i]-1]
		int l = i - d[i] + 1, r = i + d[i] - 1, len = min(n - r - 1, mx[l]);
		int res = (d[i] * 2 - 1) + len * 2;
		if (res > ans) {
			ans = res;
			if (len == 0) intervals = vector<pii>{ {l, r - l + 1} };
			else {
				intervals = vector<pii>{ {mxp[l], len}, {l, r - l + 1}, {n - len,len} };
			}
		}
	}
	cout << intervals.size() << '\n';
	for (auto [l, len] : intervals) cout << l + 1 << ' ' << len << '\n';
}
