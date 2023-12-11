// xiaoshulin
// 2023.12.11
// normal dp is TLE
class Solution {
	using ll = long long;
	using pii = pair<int, int>;
public:
    long long getSchemeCount(int n, int m, vector<string>& chessboard) {
		// O (f(min(n, m)) ^ 3 * max(n, m));
		// transpose the matrix
		vector<vector<int>> g;
		if (n < m) {
			swap(n, m);
			g = vector<vector<int>>(n, vector<int>(m));
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j) {
					if (chessboard[j][i] == '.') g[i][j] = 0;
					else if (chessboard[j][i] == 'R') g[i][j] = 1;
					else if (chessboard[j][i] == 'B') g[i][j] = 2;
					else g[i][j] = 3;
				}
		}
		else {
			g = vector<vector<int>>(n, vector<int>(m));
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j) {
					if (chessboard[i][j] == '.') g[i][j] = 0;
					else if (chessboard[i][j] == 'R') g[i][j] = 1;
					else if (chessboard[i][j] == 'B') g[i][j] = 2;
					else g[i][j] = 3;
				}
		}

		// top down enumerate the status
		// the maximum 3-dexcimal numbers is no more than 243
		vector<int> valid;

		// I might not understand the rules
		// this function is to get the all valid status
		function<void(int, int, int, int)> cal = [&](int pre1, int pre2, int p, int cur) { 
			if (p == m) {
				valid.push_back(cur);
				return;
			}
			if (pre2 == 0) {
				// 1 0 or 2 0 or 0 0
				if (pre1 == 0) {
					// 0 0
					cal(0, 0, p + 1, cur * 3); // choose 0
					cal(1, 0, p + 1, cur * 3 + 1); // choose 1
					cal(2, 0, p + 1, cur * 3 + 2); // choose 2
				}
				if (pre1 == 1) {
					// 1 0
					cal(1, 1, p + 1, cur * 3 + 1); // choose 1
					cal(1, 0, p + 1, cur * 3); // choose 0
					cal(1, 2, p + 1, cur * 3 + 2); // choose 2
				}
				if (pre1 == 2) {
					// 2 0
					cal(2, 2, p + 1, cur * 3 + 2); // choose 2
					cal(2, 1, p + 1, cur * 3 + 1); // choose 1
					cal(2, 0, p + 1, cur * 3); // choose 0
				}
			}
			else if (pre2 == 1) {
				if (pre1 == 1) {
					// 1 1
					cal(1, 1, p + 1, cur * 3 + 1); // choose 1
					cal(1, 1, p + 1, cur * 3);  // choose 0
				}
				if (pre1 == 2) {
					// 2 1
					cal(2, 1, p + 1, cur * 3); // choose 0
					cal(1, 2, p + 1, cur * 3 + 2); // choose 2
				}
			}
			else {
				if (pre1 == 1) {
					// 1 2
					cal(1, 2, p + 1, cur * 3); // choose 0
					cal(2, 1, p + 1, cur * 3 + 1); // choose 1
				}
				if (pre1 == 2) {
					// 2 2
					cal(2, 2, p + 1, cur * 3); // choose 0
					cal(2, 2, p + 1, cur * 3 + 2); // choose 2
				}
			}
		};

		auto f = [&](int a, int b, int c) -> pii { 
			if (a == 0 && b == 0) {
				// 0 0
				if (c == 0) return {0, 0};
				if (c == 1) return {1, 0};
				if (c == 2) return {2, 0};
			}
			if (a == 1 && b == 0) {
				// 1 0
				if (c == 0) return {1, 0};
				if (c == 1) return {1, 1};
				if (c == 2) return {1, 2};
			}
			if (a == 2 && b == 0) {
				// 2 0
				if (c == 0) return {2, 0};
				if (c == 1) return {2, 1};
				if (c == 2) return {2, 2};
			}
			if (a == 1 && b == 1) {
				// 1 1
				if (c == 0) return {1, 1};
				if (c == 1) return {1, 1};
				if (c == 2) return {-1, -1}; // not valid
			}
			if (a == 2 && b == 1) {
				// 2 1
				if (c == 0) return {2, 1};
				if (c == 1) return {-1, -1}; // not valid
				if (c == 2) return {1, 2};
			}
			if (a == 1 && b == 2) {
				// 1 2
				if (c == 0) return {1, 2};
				if (c == 1) return {2, 1};
				if (c == 2) return {-1, -1};
			}
			if (a == 2 && b == 2) {
				// 2 2
				if (c == 0) return {2, 2};
				if (c == 1) return {-1, -1};
				if (c == 2) return {2, 2};
			}
			return {-1, -1};
		};

		cal(0, 0, 0, 0); // calculate the status

		// get all the valid status of each row
		vector<int> row[n];
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < valid.size(); ++j) {
				int flag = 1, tmp = valid[j];
				for (int k = m - 1; k >= 0; --k) {
					if (g[i][k] < 3 && tmp % 3 != g[i][k]) {
						// is not the ? and status is not correct
						flag = 0;
						break;
					}
					tmp /= 3;
				}
				if (flag) row[i].push_back(valid[j]);
			}
		}
		
		if (n == 1) return row[0].size();
		if (n == 2) return row[0].size() * row[1].size();

		// dp
		int N = (int)pow(3, m);
		vector dp(n + 1, vector(N, vector<ll>(N)));
		vector<pii> arr[N], new_pre[N]; 
		// the most expensive part
		for (int& cur : valid) {
			for (int pre1 = 0; pre1 < N; ++pre1) {
				for (int pre2 = 0; pre2 < N; ++pre2) {
					// get the pre status
					int x = pre1, y = pre2, z = cur, flag = 1, new_pre1 = 0, new_pre2 = 0;
					for (int k = 0, w = 1; k < m; ++k, w *= 3) { 
						auto [p1, p2] = f(x % 3, y % 3, z % 3);
						if (p1 == -1) {
							flag = 0;
							break;
						}
						new_pre1 += p1 * w;
						new_pre2 += p2 * w;
						x /= 3;
						y /= 3;
						z /= 3;
					}
					if (flag) {
						arr[cur].emplace_back(pre1, pre2);
						new_pre[cur].emplace_back(new_pre1, new_pre2);
					}
				}
			}
		}
		dp[0][0][0] = 1;
		// calculate
		for (int i = 1; i <= n; ++i) {
			// what can we choose?
			for (int& c : row[i - 1]) {
				for (int x = 0; x < arr[c].size(); ++x) {
					auto [new_pre1, new_pre2] = new_pre[c][x];
					auto [pre1, pre2] = arr[c][x];
					dp[i][new_pre1][new_pre2] += dp[i - 1][pre1][pre2];
				}
			}
		}
		ll ans = 0;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j) ans += dp[n][i][j];
		return ans;
    }

};


// 7 进制动态规划
// 插头DP
class Solution {
public:
    long long getSchemeCount(int n, int m, vector<string>& a) {
        if(n < m) {
            swap(n, m);
            vector<string> b(n, "");
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j <m; ++j) b[i].push_back(a[j][i]);
            }
            a = b;
        }
        
        const int X = 0, R = 1, B = 2, R2 = 3, B2 = 4, RB = 5, BR = 6;
        int g[7][7];
        memset(g, -1, sizeof(g));
        for(int i = 0; i < 7; ++i) g[i][0] = i;

        g[X][R] = R;
        g[X][B] = B;
        g[R][R] = R2;
        g[R][B] = RB;
        g[B][R] = BR;
        g[B][B] = B2;
        g[R2][R] = R2;
        g[B2][B] = B2;
        g[RB][R] = BR;
        g[BR][B] = RB;
        
        int N = 1;
        for(int i = 0; i < m; ++i) N *= 7;
        long long f[n+1][m][N][7];
        memset(f, 0, sizeof(f));
        f[0][0][0][0] = 1;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                int ni = i, nj = j + 1;
                if(nj == m) ni++, nj = 0;
                int xp = -1;
                if(a[i][j] == 'R') xp = R;
                if(a[i][j] == 'B') xp = B;
                if(a[i][j] == '.') xp = 0;
                int base = 1;
                for(int x = 0; x < j; ++x) base *= 7;
                for(int h = 0; h < N; ++h) {
                    int st = h / base;
                    st = st % 7;
                    for(int c = 0; c < 7; ++c) {
                        for(int ne = 0; ne < 3; ++ne) {
                            if(xp == -1 || xp == ne) {
                                if(g[st][ne] != -1 && g[c][ne] != -1) {
                                    int nh = h + (g[st][ne] - st) * base;
                                    int nc = g[c][ne];
                                    if(ni != i) nc = 0;
                                    f[ni][nj][nh][nc] += f[i][j][h][c];
                                }
                            }
                        }
                    }
                }
            }
        }
        
        long long res = 0;
        for(int h = 0; h < N; ++h) {
            res += f[n][0][h][0];
        }
        
        return res;
    }
};



