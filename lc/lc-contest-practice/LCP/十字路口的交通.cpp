// xiaoshulin
// 2023.12.29

class Solution {
public:
    int trafficCommand(vector<string>& directions) {
		int dp[21][21][21][21];
		memset(dp, 0x3f, sizeof(dp));

		// constants
		unordered_map<char, int> mp[4]{
			{{'W', 0}, {'N' , 1}, {'S' , 2}},
			{{'N', 3}, {'E' , 4}, {'W' , 5}},
			{{'E', 6}, {'S' , 7}, {'N' , 8}},
			{{'S', 9}, {'W' , 10}, {'E' , 11}},
		};
		vector<vector<int>> con_idx{
			{3, 5, 8, 9, 10, 11},
			{3, 8},
			{3, 5, 6, 7, 9, 11},
			{0, 1, 2, 6, 8, 11},
			{6, 11},
			{0, 2, 6, 8, 9, 10},
			{2, 3, 4, 5, 9, 11},
			{2, 9},
			{0, 1, 3, 5, 9, 11},
			{0, 2, 5, 6, 7, 8},
			{0, 5},
			{0, 2, 3, 4, 6, 8}
		};
		vector<int> conflict(12);
		for (int i = 0; i < 12; ++i) {
			for (int& v : con_idx[i]) {
				conflict[i] |= (1 << v);
			}
		}
		vector<int> N(4);
		for (int i = 0; i < 4; ++i) {
			N[i] = directions[i].size();
		}
		dp[N[0]][N[1]][N[2]][N[3]] = 0;
		function<int(array<int, 4>)> dfs = [&](array<int, 4> p) -> int {
			if (dp[p[0]][p[1]][p[2]][p[3]] != 0x3f3f3f3f) return dp[p[0]][p[1]][p[2]][p[3]];
			int& res = dp[p[0]][p[1]][p[2]][p[3]];
			int cur = 0;
			// E S W N
			for (int i = 0; i < 4; ++i) {
				if (p[i] < N[i]) cur |= (1 << i);
			}
			for (int s = cur; s; s = (s - 1) & cur) {
				int con = 0, have = 0;
				for (int i = 0; i < 4; ++i) {
					if ((s >> i) & 1) {
						int idx = mp[i][directions[i][p[i]]];
						con |= conflict[idx];
						have |= (1 << idx);
						++p[i];
					}
				}
				if ((have & con) == 0) {
					res = min(res, 1 + dfs(p));
				}
				for (int i = 0; i < 4; ++i) {
					if ((s >> i) & 1) {
						--p[i];
					}
				}
			}
			return res;
		};
		return dfs(array<int, 4>{0, 0, 0, 0});
    }
};
