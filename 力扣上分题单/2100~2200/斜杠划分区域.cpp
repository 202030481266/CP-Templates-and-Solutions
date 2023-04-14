// https://leetcode.cn/problems/regions-cut-by-slashes/



class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
    	// 将区域看成是有四个小的三角形构造而成的区域，然后转换为连通块的问题
    	int n = grid.size(), N = n * n, fa[N * 4]; 
    	for (int i = 0; i < N * 4; ++i) fa[i] = i;

    	function<int(int)> find = [&](int x) -> int {
    		return fa[x] == x ? x : fa[x] = find(fa[x]);
    	};
    	function<void(int, int)> merge = [&](int x, int y) {
    		int f1 = find(x), f2 = find(y);
    		if (f1 != f2) fa[f2] = f1;
    	};
    	for (int i = 0 ; i < n; ++i)
    		for (int j = 0; j < n; ++j) {
    			int idx = i * n + j;
    			if (grid[i][j] == ' ') merge(idx, idx + N), merge(idx, idx + 2 * N), merge(idx, idx + 3 * N);
    			else if (grid[i][j] == '/') merge(idx, idx + 3 * N), merge(idx + N, idx + 2 * N);
    			else merge(idx, idx + N), merge(idx + 2 * N, idx + 3 * N);
    		}
    	for (int i = 0; i < n; ++i) 
    		for (int j = 0; j < n; ++j) {
    			if (j + 1 < n) merge(i * n + j + N, i * n + j + 1 + 3 * N);
    			if (i + 1 < n) merge(i * n + j + 2 * N, (i + 1) * n + j);
    		}
    	int ans = 0;
    	for (int i = 0; i < 4 * N; ++i) if (find(i) == i) ++ans;
    	return ans;
    }
};