// https://leetcode.cn/problems/beautiful-arrangement/



class Solution {
public:
	int countArrangement(int n) {
		vector<vector<int>> candi(n + 1);

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if ((i % j == 0) || (j % i == 0)) {
					candi[i].emplace_back(j - 1);  // index - 1
				}
			}
		}
		// dbg(candi);
		int N = (1 << n);
		vector dp(n + 1, vector<int>(N, -1));
		function<int(int, int)> dfs = [&](int p, int s) {
			if (p == 0) return 1;
			if (dp[p][s] != -1) return dp[p][s];
			int tmp = 0;
			for (auto c : candi[p]) {
				if ((s >> c) & 1) {
					tmp += dfs(p - 1, s ^ (1 << c));
				}
			}
			return dp[p][s] = tmp;
		};
		return dfs(n, N - 1);
	}
};

