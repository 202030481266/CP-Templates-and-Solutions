// https://leetcode.cn/problems/maximum-good-people-based-on-statements/
// 没什么技巧，就是单纯的暴力枚举所有的情况然后检验


class Solution {
public:
	// 1 <= n <= 15
	int maximumGood(vector<vector<int>>& statements) {
		int n = statements.size();
		int ans = 0;
		// 枚举所有的情况
		for (int i = 1; i < (1 << n); ++i) {
			int cnt = 0;
			for (int j = 0; j < n; ++j) {
				if ((i >> j) & 1) {
					for (int k = 0; k < n; ++k) {
						if (statements[j][k] < 2 && statements[j][k] != ((i >> k) & 1)) {
							goto next;
						}
					}
					++cnt;
				}
			}
			ans = max(ans, cnt);
		next:;
		}
		return ans;
	}
};