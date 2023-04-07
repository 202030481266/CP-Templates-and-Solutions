// https://leetcode.cn/problems/count-special-integers/
// 数位dp


class Solution {
public:
    int countSpecialNumbers(int n) {
    	string s = to_string(n);

    	int m = s.size();
    	vector dp(1 << 10, vector<int>(m, -1));

    	function<int(int, int, bool, bool)> dfs = [&](int i, int S, bool is_limit, bool is_num) -> int {
    		if (i == m) return is_num;  // 返回是否有填充了数字
    		if (!is_limit && is_num && dp[S][i] != -1) return dp[S][i];

    		int res = 0;
    		int up = is_limit ? s[i] - '0' : 9;
    		if (!is_num) {
    			res += dfs(i + 1, S, false, false);
    			for (int j = 1; j <= up; ++j) {
    				if ((S >> j) & 1) continue;
    				res += dfs(i + 1, S | (1 << j), is_limit && j == up, true);
    			}
    		}
    		else {
    			for (int j = 0; j <= up; ++j) {
    				if ((S >> j) & 1) continue;
    				res += dfs(i + 1, S | (1 << j), is_limit && j == up, true);
    			}
    		}
    		if (!is_limit && is_num) dp[S][i] = res;
    		return res;
    	};

    	return dfs(0, 0, true, false);
    }
};