// https://www.luogu.com.cn/problem/P1429 模板题目
// https://leetcode.cn/problems/beautiful-pairs/ 模板题目（字典序+曼哈顿距离）

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

// 使用欧几里得距离
long long dist2(pair<int, int> a, pair<int, int> b) {
	return 1LL * (a.first - b.first) * (a.first - b.first) + 1LL * (a.second - b.second) * (a.second - b.second);
}

// 也可以使用曼哈顿距离，只需要将dist函数修改即可。
// 所有的点不能出现重复的点，不然超时！所以需要判重！

pair<int, int> closest_pair(vector<pair<int, int>> a) {
	int n = a.size();
	assert(n >= 2);
	vector<pair<pair<int, int>, int>> p(n);
	for (int i = 0; i < n; i++) p[i] = { a[i], i };
	sort(p.begin(), p.end());
	int l = 0, r = 2;
	long long ans = dist2(p[0].first, p[1].first);
	pair<int, int> ret = { p[0].second, p[1].second };
	while (r < n) {
		// 如果需要取字典序，需要将 >= 修改为 >
		while (l < r && 1LL * (p[r].first.first - p[l].first.first) * (p[r].first.first - p[l].first.first) >= ans) l++;
		for (int i = l; i < r; i++) {
			long long nw = dist2(p[i].first, p[r].first);
			if (nw < ans) {
				ans = nw;
				ret = { p[i].second, p[r].second };
			}
		}
		r++;
	}
	return ret;
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >> n;
	vector<pair<int, int>> p(n);
	for (int i = 0; i < n; i++) cin >> p[i].first >> p[i].second;
	pair<int, int> z = closest_pair(p);
	if (z.first > z.second) swap(z.first, z.second);
	cout << z.first << ' ' << z.second << ' ' << fixed << setprecision(6) << sqrtl(dist2(p[z.first], p[z.second])) << '\n';
	return 0;
}