// https://leetcode.cn/problems/count-numbers-with-unique-digits/
// 数位dp的填充模板题目


class Solution {
public:
	int countNumbersWithUniqueDigits(int n) {
		// 0 <= n <= 8, n + 1 bits

		int N = pow(10, n);
		string s = to_string(N - 1);
		int m = s.size();
		vector dp(m, vector<int>(1 << 10, -1));
		
		// is_num control the length of number
		// is_limit control the number range of position
		function<int(int, int, bool, bool)> dfs = [&](int i, int status, bool is_limit, bool is_num) -> int {
			if (i == m) return 1;
			if (!is_limit && is_num && dp[i][status] >= 0) return dp[i][status];
			int res = 0;
			int up = (is_limit) ? s[i] - '0' : 9;
			if (!is_num) {
				// no numbers before i
				res += dfs(i + 1, status, false, false); 
				// must start from the 1
				for (int j = 1; j <= up; ++j) {
					bool exi = ((status >> j) & 1);
					if (exi) continue;
					res += dfs(i + 1, status | (1 << j), is_limit && (j == up), true);
				}
			}
			else {
				// have numbers before i
				for (int j = 0; j <= up; ++j) {
					bool exi = ((status >> j) & 1);
					if (exi) continue;
					res += dfs(i + 1, status | (1 << j), is_limit && (j == up), true);
				}
			}
			if (!is_limit && is_num) dp[i][status] = res;
			return res;
		};
		return dfs(0, 0, true, false);
	}
};