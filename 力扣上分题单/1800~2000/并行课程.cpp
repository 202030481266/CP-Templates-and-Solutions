// https://leetcode.cn/problems/parallel-courses-ii/
// 子集动态规划


class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<vector<int>> g(n + 1);
        vector<vector<int>> rely(n + 1);
        vector<int> in(n + 1);
        vector<int> r(n + 1);

        // build graph and rely
        for (auto c : relations) {
            g[c[0]].emplace_back(c[1]);
            rely[c[1]].emplace_back(c[0]);
            in[c[1]]++;
        }

        // build the begin of the graph
        for (int i = 1; i <= n; ++i)
            if (in[i] == 0) g[0].emplace_back(i);
        // build the relation status
        for (int i = 1; i <= n; ++i) {
            int S = 0;
            for (auto v : rely[i]) S = (S | (1 << v));
            r[i] = S;
        }
        // total status
        int N = (1 << (n + 1));
        vector<bool> f(N, false);
        vector<int> need(N);
        vector<int> dp(N, INT_MAX / 2);

        for (int i = 1; i < N; ++i) {
            int S = 0;
            for (int j = 1; j <= n; ++j) {
                if ((i >> j) & 1) {
                    S = (S | r[j]);
                }
            }
            need[i] = S;
        }

        // check the status whether if it is exceeded k one
        for (int i = 1; i < N; ++i) {
            int cnt = 0;
            // calculate the 1 to n nodes
            for (int j = 1; j <= n; ++j) {
                if ((i >> j) & 1) ++cnt;
            }
            if (cnt <= k) f[i] = true;
        }
        dp[1] = 0;
        for (int i = 1; i < N; ++i) {
            vector<int> node;
            for (int j = n; j >= 0; --j) {
                if ((i >> j) & 1) {
                    node.emplace_back(j);
                }
            }
            int S = 0;
            for (auto u : node) {
                for (auto v : g[u]) {
                    if (((i >> v) & 1) == 0)
                        S = (S | (1 << v));
                }
            }
            for (int sub = S; sub; sub = (sub - 1) & S) {
                if (f[sub] && ((i | need[sub]) == i))
                    dp[i | sub] = min(dp[i | sub], dp[i] + 1);
            }
        }
        return dp[N - 1];
    }
};：w