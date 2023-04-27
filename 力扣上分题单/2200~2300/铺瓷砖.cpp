// https://leetcode.cn/problems/tiling-a-rectangle-with-the-fewest-squares/



class Solution {
	int vis[20][20];
public:
    int tilingRectangle(int n, int m) {
    	// 一定有解，使用 1*1 的正方形一定可以覆盖玩所有的地板
    	// 这道题的难点在于证明是否是np完全问题，但是从数据范围上看应该是属于爆搜的题目
    	int ans = n * m;
    	memset(vis, 0, sizeof(vis));
    	function<void(int)> dfs = [&](int d) {
    		int x = -1, y = -1;
    		for (int i = 1; i <= n; ++i) {
    			bool flag = false;
    			for (int j = 1; j <= m; ++j)
    				if (!vis[i][j]) { x = i, y = j, flag = true; break; }
    			if (flag) break;
    		}
    		if (x == -1 || y == -1) { ans = min(ans, d); return; }
    		// 填充这个位置
    		if (d + 1 >= ans) return;  // 最优性剪枝
    		for (int i = 1; x + i - 1 <= n && y + i - 1 <= m; ++i) {
    			// 查看填充这个正方形是否全部没有被填充
    			bool flag = true;
    			for (int nx = x; nx <= x + i - 1; ++nx) {
    				if (!flag) break;
    				for (int ny = y; ny <= y + i - 1; ++ny)
    					if (vis[nx][ny]) { flag = false; break; }
    			}
    			if (flag) {
    				for (int nx = x; nx <= x + i - 1; ++nx)
    					for (int ny = y; ny <= y + i - 1; ++ny)
    						vis[nx][ny] = 1;
    				dfs(d + 1);
    				for (int nx = x; nx <= x + i - 1; ++nx)
    					for (int ny = y; ny <= y + i - 1; ++ny)
    						vis[nx][ny] = 0;
    			}
    		}
    	};
    	dfs(0);
    	return ans;
    }
};