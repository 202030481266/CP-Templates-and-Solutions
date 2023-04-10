/*
	1、拓扑排序是应对具有明显依赖关系又具有其他复杂依赖关系的好方法。
	2、拓扑排序具有化简图的效果，比如去掉所有不是环的节点，从叶子出发化简树的形状
*/


// 拓扑排序模板题1 https://leetcode.cn/problems/build-a-matrix-with-conditions/
// 因为题目要求的只是行与行，列与列的之间的约束关系，所以可以使用拓扑排序来确定放置的位置
class Solution {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
    	auto topu_sort = [&](vector<vector<int>>& edges) -> vector<int> {
    		vector<vector<int>> g(k);
    		vector<int> deg(k);
    		for (auto &c : edges) {
    			g[--c[0]].emplace_back(--c[1]);
    			++deg[c[1]];
    		}
    		queue<int> q;
    		for (int i = 0; i < k; ++i)
    			if (deg[i] == 0) q.emplace(i);
    		vector<int> order;
    		while (!q.empty()) {
    			int u = q.front();
    			q.pop();
    			order.emplace_back(u);
    			for (int v : g[u]) {
    				if (--deg[v] == 0) q.emplace(v);
    			}
    		}
    		return order;
    	};
    	auto rows = topu_sort(rowConditions);
    	auto cols = topu_sort(colConditions);
    	// 判断是否存在环
    	if (rows.size() != k || cols.size() != k) return {};
    	vector<int> ref(k);
    	for (int i = 0; i < k; ++i) {
    		ref[cols[i]] = i;
    	}
    	vector ans(k, vector<int>(k));
    	for (int i = 0; i < k; ++i) {
    		ans[i][ref[rows[i]]] = rows[i] + 1;
    	}
    	return ans;
    }
};


// 拓扑排序应用在无向树上，主要思想和基环树的拓扑排序类似，使用拓扑排序化简图
// 模板题目: https://leetcode.cn/problems/collect-coins-in-a-tree/
/*
	1、那么显然可以把不包含金币的子树全部删除，化简图之后就可以发现这样子得到的图中，全部的金币都是在叶子结点上。
	2、距离为2的点都可以收集到金币表明所有距离金币距离小于2的节点都不是必要的，可以有一次把这些点全部去掉。
	3、剩下的树的边都需要行走两次，因为相当于进行了一次dfs，去访问一个叶子结点当然要回来一次。
*/
class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
    	// 构建图
    	int n = coins.size();
    	int ans = n - 1;
    	vector<vector<int>> g(n);
    	vector<int> deg(n);
    	for (auto c : edges) {
    		g[c[0]].emplace_back(c[1]);
    		g[c[1]].emplace_back(c[0]);
    		++deg[c[0]], ++deg[c[1]];
    	}
    	// 拓扑排序
    	queue<int> q;
    	for (int i = 0; i < n; ++i)
    		if (deg[i] == 1 && coins[i] == 0) q.emplace(i);
    	while (!q.empty()) {
    		int u = q.front();
    		q.pop();
    		--ans; // 每一次都删除了片叶子，所以少了一条边
    		for (int v : g[u]) {
    			if (--deg[v] == 1 && coins[v] == 0) q.emplace(v);
    		}
    	}
    	// 再进行两次拓扑排序(bfs)
    	for (int i = 0; i < n; ++i)
    		if (deg[i] == 1 && coins[i] == 1) q.emplace(i);
    	ans -= q.size();
    	while (!q.empty()) {
    		int u = q.front();
    		q.pop();
    		for (int v : g[u]) {
    			if (--deg[v] == 1)
    				--ans;
    		}
    	}
    	return max(ans * 2, 0);
    }
};
// 利用进队的时间还可以计算出各种距离的答案
class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
    	// 构建图
    	int n = coins.size();
    	vector<vector<int>> g(n);
    	vector<int> deg(n);
    	for (auto c : edges) {
    		g[c[0]].emplace_back(c[1]);
    		g[c[1]].emplace_back(c[0]);
    		++deg[c[0]], ++deg[c[1]];
    	}
    	// 拓扑排序
    	queue<int> q;
    	for (int i = 0; i < n; ++i)
    		if (deg[i] == 1 && coins[i] == 0) q.emplace(i);
    	while (!q.empty()) {
    		int u = q.front();
    		q.pop();
    		for (int v : g[u]) {
    			if (--deg[v] == 1 && coins[v] == 0) q.emplace(v);
    		}
    	}
    	// 再进行两次拓扑排序(bfs)
    	for (int i = 0; i < n; ++i)
    		if (deg[i] == 1 && coins[i] == 1) q.emplace(i);
    	vector<int> time(n);
    	while (!q.empty()) {
    		int u = q.front();
    		q.pop();
    		for (int v : g[u]) {
    			if (--deg[v] == 1) {
    				time[v] = time[u] + 1;
    				q.emplace(v);
    			}
    		}
    	}
    	int ans = 0;
    	for (auto c : edges) {
    		if (time[c[0]] >= 2 && time[c[1]] >= 2) ++ans;
    	}
    	return ans * 2;
    }
};