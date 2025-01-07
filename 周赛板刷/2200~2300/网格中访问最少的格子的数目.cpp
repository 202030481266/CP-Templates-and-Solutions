// https://leetcode.cn/problems/minimum-number-of-visited-cells-in-a-grid/
// 平衡树优化稠密图


class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
    	int n = grid.size(), m = grid[0].size();
    	set<int> row[n];
    	set<int> col[m];

    	for (int i = 0; i < n; ++i) 
    		for (int j = 0; j < m; ++j)
    			row[i].emplace(i * m + j);
    	for (int i = 0; i < m; ++i)
    		for (int j = 0; j < n; ++j)
    			col[i].emplace(j * m + i);

    	vector<int> q{0};
    	for (int d = 0; !q.empty(); ++d) {
    		vector<int> tmp;
    		for (int k = 0; k < q.size(); ++k) {
    			int i = q[k] / m, j = q[k] % m;
    			if (i == n - 1 && j == m - 1) return d + 1;
    			// 往右移动
    			int right = i * m + min(m - 1, grid[i][j] + j);
    			auto &s = row[i];
    			for (auto it = s.lower_bound(i * m + j + 1); it != s.end() && *it <= right; it = s.erase(it)) {
    				int idx = *it, cl = idx % m;
    				tmp.emplace_back(idx);
    				auto col_it = col[cl].find(idx);
    				if (col_it != col[cl].end()) col[cl].erase(col_it);
    			}
    			// 往下移动
    			int down = min(n - 1, grid[i][j] + i) * m + j;
    			auto &ss = col[j];
    			for (auto it = ss.lower_bound((i + 1) * m + j); it != ss.end() && *it <= down; it = ss.erase(it)) {
    				int idx = *it, rw = idx / m;
    				tmp.emplace_back(idx);
    				auto row_it = row[rw].find(idx);
    				if (row_it != row[rw].end()) row[rw].erase(row_it);
    			}
    		}
    		q = move(tmp);
    	}
    	return -1;
    }
};