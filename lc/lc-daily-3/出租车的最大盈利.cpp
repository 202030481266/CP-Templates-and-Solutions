// xiaoshulin
// 2023.12.8

class Solution {
	using pii = pair<int, int>;
public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
		int m = rides.size();

		vector<pii> g[n + 1];
		for (auto& p : rides) {
			g[p[1]].emplace_back(p[0], p[1] - p[0] + p[2]);
		}

		vector<long long> dp(n + 1);
		for (int i = 1; i <= n; ++i) {
			dp[i] = dp[i - 1];
			if (g[i].size()) {
				for (auto [st, val] : g[i])
					// [st, i)
					dp[i] = max(dp[i], dp[st] + val);
			}
		}
		return dp[n];
    }
};
