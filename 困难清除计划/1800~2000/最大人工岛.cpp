// https://leetcode.cn/problems/making-a-large-island/



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
public:
    int largestIsland(vector<vector<int>>& grid) {
    	int n = grid.size();

    	vector<int> dx{-1, 1, 0, 0};
    	vector<int> dy{0, 0, 1, -1};

    	auto f = [&](int x, int y) {
    		return (x >= 0) && (y >= 0) && (x < n) && (y < n);
    	};

    	UnionFind un(n * n);
    	int cnt1 = 0;
    	for (int i = 0; i < n; ++i) {
    	 	for (int j = 0; j < n; ++j) {
    	 		if (grid[i][j]) {
    	 			for (int k = 0; k < 4; ++k) {
    	 				int nx = i + dx[k], ny = j + dy[k];
    	 				if (f(nx, ny) && grid[nx][ny]) {
    	 					un.unite(nx * n + ny, i * n + j);
    	 				}
    	 			}
    	 			++cnt1;
    	 		}
    	 	}
    	}
    	if (cnt1 == n * n) return n * n;
    	int ans = 0;
    	for (int i = 0; i < n; ++i) {
    		for (int j = 0; j < n; ++j) {
    			if (grid[i][j]) continue;
    			int t = 1; // itself
    			unordered_set<int> adj;
    			for (int k = 0; k < 4; ++k) {
	 				int nx = i + dx[k], ny = j + dy[k];
	 				if (f(nx, ny) && grid[nx][ny]) {
	 					adj.emplace(un.find(nx * n + ny));
	 				}
	 			}
	 			for (auto v : adj)
	 				t += un.size[v];
	 			ans = max(ans, t);
    		}
    	}
    	return ans == 0 ? 1 : ans;
    }
};