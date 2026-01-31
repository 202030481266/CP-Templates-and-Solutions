// xiaoshulin
// 2023.12.19

class Solution {
public:
    int defendSpaceCity(vector<int>& time, vector<int>& position) {
		// 轮廓线DP
		// O((4 ^ m) * n * m)
		// max complexity is 5 * 10^5

		int n = time.size();
		int N = *max_element(position.begin(), position.end());
		int T = *max_element(time.begin(), time.end());

		vector<vector<int>> a(N + 1, vector<int>(T));

		for (int i = 0; i < n; ++i)
			a[position[i]][time[i] - 1] = 1;  // time [1, 5] -> [0, 4]

		int dp[2][1 << 10];
		memset(dp, 0x3f, sizeof(dp));
		int *pre = dp[0];
		int *nxt = dp[1];
		pre[0] = 0;

		const int inf = 0x3f3f3f3f;

		for (int i = 0; i <= N; ++i) {
			for (int j = 0; j < T; ++j) {
				for (int s = 0; s < (1 << T * 2); ++s) {
					// every column status is 2 bits
					int t = ((s >> 2 * j) & 3);
					int s0 = (s ^ (t << 2 * j));
					nxt[s] = inf;
					if (t == 0) {
						// it is empty
						if (!a[i][j]) {
							// allow empty
							// the pre status should be 0, 1, 2
							int s1 = s0 | (1 << 2 * j);
							int s2 = s0 | (2 << 2 * j);
							nxt[s] = min(pre[s0], min(pre[s1], pre[s2]));
						}
					}
					else if (t == 1) {
						// it is unique one
						// then the previous status can be 0, 1, 2 
						int s1 = s0 | (1 << 2 * j);
						int s2 = s0 | (2 << 2 * j);
						if (j > 0 && ((s >> 2 * (j - 1)) & 3) == t) {
							nxt[s] = min(pre[s0], min(pre[s1], pre[s2])) + 1;
						}
						else {
							nxt[s] = min(pre[s0], min(pre[s1], pre[s2])) + 2;
						}
					}
					else if (t == 2) {
						// it is the union one
						// then the previous status should be 3 
						int s3 = s0 | (3 << 2 * j);
						nxt[s] = pre[s3];
					}
					else {
						// it is 3
						// the previous status should be 0, 1, 2
						int s1 = s0 | (1 << 2 * j);
						int s2 = s0 | (2 << 2 * j);
						if (j > 0 && ((s >> 2 * (j - 1)) & 3) == t) {
							nxt[s] = min(pre[s0], min(pre[s1], pre[s2])) + 1;
						}
						else {
							nxt[s] = min(pre[s0], min(pre[s1], pre[s2])) + 3;
						}
					}
				}
				swap(nxt, pre);
			}
		}
		int ans = inf;
		for (int i = 0; i < (1 << T * 2); ++i) {
			bool flag = 1;
			for (int j = 0; j < T; ++j) {
				if ((i >> 2 * j) == 3) {
					flag = false;
					break;
				}
			}
			if (flag) ans = min(ans, pre[i]);
		}
		return ans;
    }
};
