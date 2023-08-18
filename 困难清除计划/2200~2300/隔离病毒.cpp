// https://leetcode.cn/problems/contain-virus/



class UnionFind {
public:
    vector<int> parent, size;
    int n, setCount;
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
class Solution {
	typedef pair<int, int> pii;
	static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int containVirus(vector<vector<int>>& isInfected) {
    	int n = isInfected.size(), m = isInfected[0].size(), vis[n][m], del[n * m], a[n][m], cost = 0;
    	memset(vis, 0, sizeof(vis));
    	memset(del, 0, sizeof(del));
    	memset(a, 0, sizeof(a));
    	UnionFind un(n * m); // 检查连通性
    	unordered_set<int> scc[n * m]; // 连通块的点集合
    	for (int i = 0; i < n; ++i)
    		for (int j = 0; j < m; ++j)
    			if (isInfected[i][j]) {
    				vis[i][j] = 1;
    				for (int k = 0; k < 4; ++k) {
    					int nx = i + dirs[k][0], ny = j + dirs[k][1];
    					if (nx < 0 || ny < 0 || nx >= n || ny >= m || !isInfected[nx][ny]) continue;
    					un.unite(i * m + j, nx * m + ny);
    				}
    			}
    	for (int i = 0; i < n * m; ++i)
    		if (vis[i / m][i % m]) scc[un.find(i)].emplace(i);  // 感染的连通块
    	vector<int> q; // 当前的连通块
    	for (int i = 0; i < n * m; ++i) if (scc[i].size()) q.emplace_back(i);  // 把连通块的祖先加入到集合里面
    	// 一直到没有更进一步的感染就退出循环
    	while (!q.empty()) {
    		vector<vector<int>> nxt(q.size());
    		for (int i = 0; i < q.size(); ++i) {
    			memset(a, 0, sizeof(a));
    			for (int p : scc[q[i]]) {
    				int x = p / m, y = p % m;
    				for (int k = 0; k < 4; ++k) {
    					int nx = x + dirs[k][0], ny = y + dirs[k][1];
    					if (nx < 0 || ny < 0 || nx >= n || ny >= m || vis[nx][ny] || a[nx][ny]) continue; 
    					a[nx][ny] = 1;
    					nxt[i].emplace_back(nx * m + ny);
    				}
    			}
    		}
    		// 找到威胁最大的连通块
    		int tar = 0;
    		for (int i = 1; i < q.size(); ++i)
    			if (nxt[i].size() > nxt[tar].size()) tar = i;
    		// 去除掉最大威胁的连通块，计算其中的费用
    		del[q[tar]] = 1;
    		for (int v : scc[q[tar]]) {
    			int x = v / m, y = v % m;
    			for (int k = 0; k < 4; ++k) {
    				int nx = x + dirs[k][0], ny = y + dirs[k][1];
    				if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
    				if (!vis[nx][ny]) ++cost;
    			}
    		}
    		// 感染
    		for (int i = 0; i < q.size(); ++i)
    			if (i != tar) 
    				for (int p : nxt[i]) {
    					int x = p / m, y = p % m;
    					vis[x][y] = 1;  // 感染
    					for (int k = 0; k < 4; ++k) {
    						int nx = x + dirs[k][0], ny = y + dirs[k][1];
    						// 不能和已经删除的方块连接
    						if (nx < 0 || ny < 0 || nx >= n || ny >= m || !vis[nx][ny] || del[un.find(nx * m + ny)]) continue; 
    						un.unite(p, nx * m + ny);
    					}
    				}
    		q = vector<int>{};
    		for (int i = 0; i < n * m; ++i)
    			if (vis[i / m][i % m]) scc[un.find(i)].emplace(i);
    		for (int i = 0; i < n * m; ++i)
    			if (!del[i] && scc[i].size()) q.emplace_back(i);
    	}
    	return cost;
    }
};