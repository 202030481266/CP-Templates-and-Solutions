// https://leetcode.cn/problems/pyramid-transition-matrix/
// 想了很久，感觉除了爆搜没有好的做法，真的很无语, 但是标准解法就是爆搜
// 使用cache进行记忆化加速居然非常快！看来数据是很假的


class Solution {
public:
	bool pyramidTransition(string bottom, vector<string>& allowed) {
		int n = bottom.size();
		vector<vector<char>> h(100);
		unordered_map<string, bool> cache;

		for (auto c : allowed) {
			int key = (c[0] - 'A') * 10 + (c[1] - 'A');
			h[key].emplace_back(c[2]);
		}
		function<void(vector<int>&, vector<string>&, int, string)> f = [&](vector<int>& a, vector<string>& res, int depth, string cur) {
			if (cur.size() == depth) {
				res.emplace_back(cur);
				return;
			}
			int k = cur.size();
			for (auto v : h[a[k]]) {
				f(a, res, depth, cur + v);
			}
		};

		function<bool(string)> dfs = [&](string status) -> bool {
			if (status.size() == 1) {
				return true;
			}
			if (cache.count(status)) {
				return cache[status];
			}
			vector<int> cur;
			for (int i = 0; i < status.size() - 1; ++i) {
				int tmp = (status[i] - 'A') * 10 + (status[i + 1] - 'A');
				cur.emplace_back(tmp);
			}
			vector<string> candi;
			f(cur, candi, cur.size(), "");
			bool ok = false;
			for (string c : candi) {
				ok = ok || dfs(c);
				if (ok) break;
			}
			return cache[status] = ok;
		};
		return dfs(bottom);
	}
};
