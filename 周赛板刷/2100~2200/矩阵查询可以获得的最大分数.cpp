// https://leetcode.cn/problems/maximum-number-of-points-from-grid-queries/



class Solution {
	static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
    	int n = grid.size(), m = grid[0].size(), vis[n][m], sum = 0;
    	memset(vis, 0, sizeof(vis));
    	vector<int> ans(queries.size());
    	vector<pair<int, int>> qs;
    	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> q;
    	// dfs
    	function<void(int, int, int)> dfs = [&](int x, int y, int mx) {
    		++sum;
    		for (int i = 0; i < 4; ++i) {
    			int nx = x + dirs[i][0], ny = y + dirs[i][1];
    			if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
    			if (!vis[nx][ny]) {
    				vis[nx][ny] = true;
    				if (grid[nx][ny] < mx) dfs(nx, ny, mx);
    				else q.emplace(grid[nx][ny], nx, ny);
    			}
    		}
    	};
    	for (int i = 0; i < queries.size(); ++i) qs.emplace_back(queries[i], i);
    	sort(qs.begin(), qs.end());
    	q.emplace(grid[0][0], 0, 0);
    	vis[0][0] = true;
    	for (int i = 0; i < qs.size(); ++i) {
			while (!q.empty() && get<0>(q.top()) < qs[i].first) {
				dfs(get<1>(q.top()), get<2>(q.top()), qs[i].first);
				q.pop();
			}
			ans[qs[i].second] = sum;
    	}
    	return ans;
    }
};