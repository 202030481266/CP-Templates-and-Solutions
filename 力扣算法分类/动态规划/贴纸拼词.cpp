// https://leetcode.cn/problems/stickers-to-spell-word/



struct HashFunc_t
{
	size_t operator() (const vector<int>& key) const {
		std::hash<int> hasher;
		size_t seed = 0;
		for (int i : key) {
			seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
}; // 使用map会超时因此使用自定义的哈希函数
class Solution {
public:
	int minStickers(vector<string>& stickers, string target) {
		int n = stickers.size();
		vector a(n + 1, vector<int>(26, 0));

		for (int i = 0; i < n; ++i) {
			for (auto ch : stickers[i]) ++a[i][ch - 'a'];
		}

		// 状态哈希
		unordered_map<vector<int>, int, HashFunc_t> dp;
		dp[a[n]] = 0;

		function<int(vector<int>)> dfs = [&](vector<int> s) -> int {
			if (dp.count(s)) {
				return dp[s];
			}
			int res = 0x3f3f3f3f;
			for (int i = 0; i < n; ++i) {
				vector<int> tmp(26, 0);
				bool flag = false;
				for (int j = 0; j < 26; ++j) {
					if (s[j] > 0 && a[i][j] > 0) {
						flag = true;  //  use it is useful
						break;
					}
				}
				if (!flag) continue;  
				for (int j = 0; j < 26; ++j)
					tmp[j] = max(0, s[j] - a[i][j]);
				res = min(res, dfs(tmp) + 1);
			}
			return dp[s] = res;
		};
		vector<int> cur(26, 0);
		for (auto ch : target) ++cur[ch - 'a'];
		int ans = dfs(cur);
		return ans == 0x3f3f3f3f ? -1 : ans;
	}
};