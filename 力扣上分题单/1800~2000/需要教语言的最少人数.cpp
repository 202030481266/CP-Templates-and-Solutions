// https://leetcode.cn/problems/minimum-number-of-people-to-teach/



class Solution {
public:
	int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
		int m = languages.size();
		vector<unordered_set<int>> l(m + 1);

		for (int i = 0; i < m; ++i) {
			for (auto c : languages[i])
				l[i + 1].emplace(c);
		}

		unordered_set<int> nodes;
		for (auto c : friendships) {
			bool flag = true;
			for (auto p : l[c[0]]) 
				if (l[c[1]].count(p)) {
					flag = false;
					break;
				}
			if (flag) {
				nodes.emplace(c[0]);
                nodes.emplace(c[1]);
			}
		}

		vector<int> cnt(n + 1);
		for (auto node : nodes) {
			for (auto v : l[node])
				++cnt[v];
		}
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			ans = max(ans, cnt[i]);
		return nodes.size() - ans;
	}
};