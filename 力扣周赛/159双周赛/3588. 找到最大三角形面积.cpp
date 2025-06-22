#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
	long long maxArea(vector<vector<int>>& coords) {
		ranges::sort(coords);
		int n = coords.size();
		int p = 0, st = coords[0][0], ed = coords[n - 1][0];
		ll ans = 0;
		while (p < n) {
			int i = p + 1;
			while (i < n && coords[i][0] == coords[p][0]) ++i;
			int y = coords[i - 1][1] - coords[p][1];
			ans = max(ans, (ll)y * max(coords[p][0] - st, ed - coords[p][0]));
			p = i;
		}
		ranges::sort(coords, [&](const auto& p1, const auto& p2) {
			return p1[1] != p2[1] ? p1[1] < p2[1] : p1[0] < p2[0];
			});
		st = coords[0][1], ed = coords[n - 1][1];
		p = 0;
		while (p < n) {
			int i = p + 1;
			while (i < n && coords[i][1] == coords[p][1]) ++i;
			int x = coords[i - 1][0] - coords[p][0];
			ans = max(ans, (ll)x * max(coords[p][1] - st, ed - coords[p][1]));
			p = i;
		}
		return ans == 0 ? -1 : ans;
	}
};