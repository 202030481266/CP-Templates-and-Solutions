#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 非常有趣的题目

class Solution {
public:
    vector<vector<int>> seePeople(vector<vector<int>>& heights) {
        // 单调上升子序列问题
        int n = heights.size(), m = heights[0].size(), N = max(n, m), dp[N+1];
        vector ans(n, vector<int>(m));
        auto cal_row = [&](int row) {
            stack<int> s,ss;
            memset(dp, -1, sizeof(dp));
            vector<int> r(m,m), rr(m,m);
            for (int i = 0; i < m; ++i) {
                while (!s.empty() && heights[row][s.top()] < heights[row][i]) {
                    r[s.top()] = i;
                    s.pop();
                }
                while (!ss.empty() && heights[row][ss.top()] <= heights[row][i]) {
                    rr[ss.top()] = i;
                    ss.pop();
                }
                s.push(i);
                ss.push(i);
            }
            dp[m] = 0;
            for (int i = 0; i < m; ++i) {
                if (dp[i] != -1) continue;
                vector<int> tmp;
                int cur = i;
                while (dp[cur] == -1) {
                    tmp.push_back(cur);
                    cur = r[cur];
                }
                dp[tmp.back()] = dp[cur]+1;
                for (int i = tmp.size()-2; i >= 0; --i) {
                    dp[tmp[i]] = dp[tmp[i+1]] + 1;
                }
            }
            for (int i = 0; i < m-1; ++i) {
                if (heights[row][i+1] >= heights[row][i]) ans[row][i] += 1;
                else {
                    ans[row][i] += dp[i+1]-dp[rr[i]]+(rr[i] == m ? 0 : 1);
                }
            }
        };
        auto cal_col = [&](int col) {
            stack<int> s,ss;
            memset(dp, -1, sizeof(dp));
            vector<int> r(n,n), rr(n,n);
            for (int i = 0; i < n; ++i) {
                while (!s.empty() && heights[s.top()][col] < heights[i][col]) {
                    r[s.top()] = i;
                    s.pop();
                }
                while (!ss.empty() && heights[ss.top()][col] <= heights[i][col]) {
                    rr[ss.top()] = i;
                    ss.pop();
                }
                s.push(i);
                ss.push(i);
            }
            dp[n] = 0;
            for (int i = 0; i < n; ++i) {
                if (dp[i] != -1) continue;
                vector<int> tmp;
                int cur = i;
                while (dp[cur] == -1) {
                    tmp.push_back(cur);
                    cur = r[cur];
                }
                dp[tmp.back()] = dp[cur]+1;
                for (int i = tmp.size()-2; i >= 0; --i) {
                    dp[tmp[i]] = dp[tmp[i+1]] + 1;
                }
            }
            for (int i = 0; i < n-1; ++i) {
                if (heights[i+1][col] >= heights[i][col]) ans[i][col] += 1;
                else {
                    ans[i][col] += dp[i+1]-dp[rr[i]]+(rr[i] == n ? 0 : 1);
                }
            }
        };
        for (int i = 0; i < n; ++i) cal_row(i);
        for (int i = 0; i < m; ++i) cal_col(i);
        return ans;
    }
};