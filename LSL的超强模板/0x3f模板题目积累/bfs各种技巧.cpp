/*
	1、bfs通常用来进行搜索最短路，那么在状态图上的bfs相当于动态规划中的最短路
	2、使用平衡树可以优化稠密图的bfs，非常nice的技巧，使用set即可做到
*/



// 难题模板1：https://leetcode.cn/problems/minimum-reverse-operations/
// 暴力枚举bfs进行动态规划会超时，但是已经访问过的下标可以使用set进行维护
class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        unordered_set<int> ban;
        for (int u : banned) ban.emplace(u);

        set<int> sets[2];
        for (int i = 0; i < n; ++i) {
        	// 需要分为奇偶下标，因为搜索的范围是公差为2的数字，所以所有的数字奇偶性相同
            if (!ban.count(i) && i != p) sets[i % 2].emplace(i);
        }
        // 哨兵技巧
        sets[0].emplace(n);
        sets[1].emplace(n);
        vector<int> ans(n, -1);
        vector<int> q{p};
        for (int i = 0; !q.empty(); ++i) {
            vector<int> tmp;
            for (int u : q) {
                ans[u] = i;
                // 下标推导比较繁琐，需要大量例子来找规律
                int left = max(u - k + 1, k - 1 - u);
                int right = min(u + k - 1, 2 * n - k - 1 - u);
                auto &s = sets[left % 2];
                for (auto it = s.lower_bound(left); *it <= right; it = s.erase(it)) {
                    // 边删边遍历
                    tmp.push_back(*it);
                }
            }
            q = move(tmp);
        }
        return ans;
    }
};




// 难题模板2：https://leetcode.cn/problems/minimum-number-of-visited-cells-in-a-grid/
// 平衡树优化稠密图，同样是使用set来进行维护，不过很简单的就是分行分列来进行，复杂度为O(nlogn)
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


// 难题模板3： https://leetcode.cn/problems/divide-nodes-into-the-maximum-number-of-groups/
// bfs+二分图判定技巧（bfs可以用来进行编号）
/*
    1、想想简单的图——树，可以发现一定有解，并且最大的分组的数目和选择编号的起点有关系
    2、可以证明，如果存在奇数的环，那么图是无解的。
    3、|x-y|=1，表明编号没走一次边就会改变奇偶性质，那么如果对于奇数环来说一定存在两个奇偶相同，无解
    4、图可解等价于二分图判定，最大的编号只能是暴力枚举+bfs，对于树而言可以使用两次dfs找到树的直径
*/
class Solution {
public:
    int magnificentSets(int n, vector<vector<int>> &edges) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            int x = e[0] - 1, y = e[1] - 1;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        int time[n], clock = 0; 
        memset(time, 0, sizeof(time));
        auto bfs = [&](int start) -> int {
            int depth = 0;
            time[start] = ++clock;
            vector<int> q = {start};
            while (!q.empty()) {
                vector<int> nxt;
                for (int x : q)
                    for (int y : g[x])
                        if (time[y] != clock) { 
                            time[y] = clock;
                            nxt.push_back(y);
                        }
                q = move(nxt);
                ++depth;
            }
            return depth;
        };

        int8_t color[n]; memset(color, 0, sizeof(color));
        vector<int> nodes;
        function<bool(int, int8_t)> is_bipartite = [&](int x, int8_t c) -> bool { 
            nodes.push_back(x);
            color[x] = c;
            for (int y : g[x])
                if (color[y] == c || color[y] == 0 && !is_bipartite(y, -c))
                    return false;
            return true;
        };

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (color[i]) continue;
            nodes.clear();
            if (!is_bipartite(i, 1)) return -1; 
            int max_depth = 0;
            for (int x : nodes) 
                max_depth = max(max_depth, bfs(x));
            ans += max_depth;
        }
        return ans;
    }
};

