// xiaoshulin
// 2023.12.10

class Solution {
public:
    int getMaximumNumber(vector<vector<int>>& mole) {
		int n = mole.size(), dp[2][3][3];
		memset(dp, -1, sizeof(dp));

		// sort 
		sort(mole.begin(), mole.end());

		int cur = 1, pre = 0, last = 0;
		for (int i = 0; i < n; ++i) {
			// no move
			memcpy(dp[cur], dp[pre], sizeof(dp[cur]));
			// at the start
			if (i == 0) dp[pre][1][1] = dp[cur][1][1] = 0;
			// allow position at the last time
			// many target at the same time
			int j = i;
			while (j < n && mole[j][0] == mole[i][0]) ++j;
			// [i, j) is the same time
			int walk = mole[i][0] - last;
			if (mole[i][0] == 0) {
				// cannot move
				for (int k = i; k < j; ++k) {
					if (mole[k][1] == 1 && mole[k][2] == 1) dp[cur][1][1] = 1;
				}
			}
			else {
				for (int k = i; k < j; ++k) {
					for (int x = 0; x < 3; ++x)
						for (int y = 0; y < 3; ++y)
							if (abs(mole[k][1] - x) + abs(mole[k][2] - y) <= walk && dp[pre][x][y] != -1)
								dp[cur][mole[k][1]][mole[k][2]] = max(dp[pre][x][y] + 1, dp[cur][mole[k][1]][mole[k][2]]);
				}
				for (int x = 0; x < 3; ++x)
					for (int y = 0; y < 3; ++y)
						for (int nx = 0; nx < 3; ++nx)
							for (int ny = 0; ny < 3; ++ny)
								if (abs(nx - x) + abs(ny - y) <= walk && dp[pre][x][y] != -1)
									dp[cur][nx][ny] = max(dp[cur][nx][ny], dp[pre][x][y]);
			}

			last = mole[i][0];
			i = j - 1;
			cur ^= 1;
			pre ^= 1;
		}
		int ans = 0;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				ans = max(ans, dp[pre][i][j]);
		return ans;
    }
};
