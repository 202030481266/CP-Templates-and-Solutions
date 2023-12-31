// xiaoshulin
// 2023.12.24
class Solution {
	using pii = pair<int, int>;
public:
    int maxWeight(vector<vector<int>>& edges, vector<int>& value) {
		// seems it is a very difficult problem
		// may be a good idea is to use the bfs tree
		// total 2 situations
		// assume that we can find the all triangles, but seems it is also very difficult
		// there is a very important rule: assume xab is the most biggest triangle around the x, then a, b will appear at the same time!
		int n = value.size(), m = edges.size();

		// 大体思路基本是一致的：想找出所有的三角形然后分类讨论（分类讨论难度巨大）
		// 找出所有的三角形一种可以使用BFS树来找（我个人的解法），但是常数偏高，更加好的做法是使用rank的技巧
		// 分类讨论使用贪心大大减少了搜索范围，思维难度非常高！

		sort(edges.begin(), edges.end(), [&](vector<int>& a, vector<int>& b) {
				return value[a[0]] + value[a[1]] > value[b[0]] + value[b[1]];
		});

		vector<int> cnt(n);
		vector<pii> g[n];
		for (int i = 0; i < m; ++i) {
			++cnt[edges[i][0]];
			++cnt[edges[i][1]];
		}
		for (int i = 0; i < m; ++i) {
			if (cnt[edges[i][0]] < cnt[edges[i][1]] || (cnt[edges[i][0]] == cnt[edges[i][1]] && edges[i][0] < edges[i][1])) {
				g[edges[i][0]].emplace_back(edges[i][1], i);
			}
			else {
				g[edges[i][1]].emplace_back(edges[i][0], i);
			}
		}
		vector<int> vis(n, 0x3f3f3f3f), idx(n);
		vector<int> nodes[m];
		for (int i = 0; i < m; ++i) {
			for (pii& adj : g[edges[i][0]]) {
				vis[adj.first] = i; 
				idx[adj.first] = adj.second;
			}
			for (pii& adj : g[edges[i][1]]) {
				if (vis[adj.first] == i) {
					// adj.first, edges[i][1], edges[i][0] have construct a triple circle
					// adj.first -> i, edges[i][0] -> adj.second, edges[i][1] -> idx[adj.first]
					nodes[i].push_back(adj.first);
					nodes[adj.second].push_back(edges[i][0]);
					nodes[idx[adj.first]].push_back(edges[i][1]);
				}
			}
		}
		vector<int> a[n];
		for (int i = 0; i < m; ++i) {
			for (int& v : nodes[i]) {
				a[v].push_back(i);
			}
		}
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			int bound = a[i].size() - 1;
			for (int x = 0; x < min(3, (int)a[i].size()) && x <= bound; ++x) {
				for (int y = 0; y <= bound; ++y) {
					int cur = value[edges[a[i][x]][0]] + value[edges[a[i][x]][1]] + value[i], cnt = 0;
					if (edges[a[i][y]][0] != edges[a[i][x]][0] && edges[a[i][y]][0] != edges[a[i][x]][1]) {
						++cnt;
						cur += value[edges[a[i][y]][0]];
					}
					if (edges[a[i][y]][1] != edges[a[i][x]][0] && edges[a[i][y]][1] != edges[a[i][x]][1]) {
						++cnt;
						cur += value[edges[a[i][y]][1]];
					}
					ans = max(ans, cur);
					// 剪枝， W(1) + W(i) >= W(2) + W(i + k)，后面的边就不需要搜索了
					if (cnt == 2) {
						bound = y - 1;
						break;
					}
				}
			}
		}
		return ans;
    }
};
