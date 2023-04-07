// https://leetcode.cn/problems/last-day-where-you-can-still-cross/



class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
    	// 寻找到最后一天存在一条路径能够从最上面走到最下面
    	vector f(row + 1, vector<int>(col + 1, 0));
    	vector<int> dx{1, 0, -1, 0};
    	vector<int> dy{0, 1, 0, -1};

    	function<void(int, int)> dfs = [&](int i, int j) {
    		f[i][j] = 2;
    		for (int k = 0; k < 4; ++k) {
    			int nx = i + dx[k], ny = j + dy[k];
    			if (nx < 1 || ny < 1 || nx > row || ny > col) continue;
    			if (f[nx][ny] == 0) {
    				dfs(nx, ny);
    			}
    		}
    	};

    	auto cal = [&](int days) -> bool {
    		for (int i = 1; i <= row; ++i)
					fill(f[i].begin(), f[i].end(), 0);
    		for (int i = 0; i <= days; ++i) {
    			f[cells[i][0]][cells[i][1]] = 1;
    		}
    		for (int i = 1; i <= col; ++i) {
    			if (f[1][i] == 0) dfs(1, i);
    		}
    		for (int i = 1; i <= col; ++i) {
    			if (f[row][i] == 2) return true;
    		}
    		return false;
    	};

    	int l = 0, r = cells.size() - 1, ans;
    	while (l <= r) {
    		int mid = (l + r) >> 1;
				cerr << mid << endl;
    		if (cal(mid)) ans = mid, l = mid + 1;
    		else r = mid - 1;
    	}
    	return ans + 1;
    }
};