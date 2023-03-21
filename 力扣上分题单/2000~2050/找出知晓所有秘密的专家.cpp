// https://leetcode.cn/problems/find-all-people-with-secret/



class Solution {
public:
	vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
		vector<vector<pair<int, int>>> g(n);

		for (auto c : meetings) {
			g[c[0]].emplace_back(c[1], c[2]);
			g[c[1]].emplace_back(c[0], c[2]);
		}
		vector<int> a(n, -1);
		a[0] = a[firstPerson] = 0;
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
		q.emplace(0, 0);
		q.emplace(0, firstPerson);

		while (!q.empty()) {
			auto [ut, u] = q.top();
			q.pop();
			for (auto [v, t] : g[u]) {
				if (a[u] > t) continue;
				if (a[v] == -1 || (a[v] > t)) {
					a[v] = t;
					q.emplace(a[v], v);
				}
			}
		}
		vector<int> ans;
		for (int i = 0; i < n; ++i) {
			if (a[i] != -1) ans.emplace_back(i);
		}
		return ans;
	}
};