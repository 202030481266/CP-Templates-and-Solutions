// xiaoshulin
// 2023.12.20
class Solution {
public:
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
		int dis[n][n];

		auto check = [&](int s) -> bool {
			memset(dis, 0x3f, sizeof(dis));
			for (auto& e : roads) {
				int x = e[0], y = e[1];
				if (((s >> x) & 1) && ((s >> y) & 1)) {
					dis[x][y] = min(dis[x][y], e[2]);
					dis[y][x] = min(dis[y][x], e[2]);
				}
			}
			for (int i = 0; i < n ; ++i) dis[i][i] = 0;
			// 正确的Floyd算法实现应该是枚举中间转移的点为第一层循环！
			for (int k = 0; k < n; ++k) {
				if ((s >> k) & 1 == 0) continue;
				for(int i = 0; i < n; ++i) {
					if ((s >> i) & 1 == 0) continue;
					for (int j = 0; j < n; ++j) {
						if ((s >> j) & 1 == 0) continue;
						dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
					}
				}
			}
			for (int i = 0; i < n; ++i)
				for (int j = i + 1; j < n; ++j)
					if (((s >> i) & 1) && ((s >> j) & 1) && dis[i][j] > maxDistance) return false;
			return true;
		};

		int ans = 0;
		for (int i = 0; i < (1 << n); ++i) {
			if (check(i)) ++ans;
		}
		return ans;
    }
};
