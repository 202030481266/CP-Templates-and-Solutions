#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 非常琐碎的一道题目，实现起来有点麻烦（很绕）
// 思维难度不大，实现难度巨大 (GPT还真写不出来)

class Solution {
public:
    long long maximumValueSum(vector<vector<int>>& board) {
        int n = board.size(), m = board[0].size();
    
        vector pre(n + 2, vector<ll>(m + 2, -inf));
        vector suf(n + 2, vector<ll>(m + 2, -inf));
        vector pre_down(n + 2, vector<pll>(m + 2, {-inf,-inf}));
        vector suf_down(n + 2, vector<pll>(m + 2, {-inf,-inf}));
        vector pre_down_pos(n + 2, vector<int>(m + 2, -1));
        vector suf_down_pos(n + 2, vector<int>(m + 2, -1));
        vector pre_up(n + 2, vector<pll>(m + 2, {-inf, -inf}));
        vector suf_up(n + 2, vector<pll>(m + 2, {-inf, -inf}));
        vector pre_up_pos(n + 2, vector<int>(m + 2, -1));
        vector suf_up_pos(n + 2, vector<int>(m + 2, -1));
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                pre[i][j] = max(pre[i][j-1], (ll)board[i-1][j-1]);
            }
            for (int j = m; j >= 1; --j) {
                suf[i][j] = max(suf[i][j+1], (ll)board[i-1][j-1]);
            }
        }
        for (int j = 1; j <= m; ++j) {
            for (int i = 1; i <= n; ++i) {
                if (pre[i][j] > pre_down[i-1][j].first) {
                    pre_down_pos[i][j] = i;
                    pre_down[i][j].second = pre_down[i-1][j].first;
                    pre_down[i][j].first = pre[i][j];
                }
                else {
                    pre_down[i][j] = pre_down[i-1][j];
                    pre_down_pos[i][j] = pre_down_pos[i-1][j];
                    if (pre[i][j] > pre_down[i-1][j].second) {
                        pre_down[i][j].second = pre[i][j];
                    }
                }
                if (suf[i][j] > suf_down[i-1][j].first) {
                    suf_down_pos[i][j] = i;
                    suf_down[i][j].second = suf_down[i-1][j].first;
                    suf_down[i][j].first = suf[i][j];
                }
                else {
                    suf_down[i][j] = suf_down[i-1][j];
                    suf_down_pos[i][j] = suf_down_pos[i-1][j];
                    if (suf[i][j] > suf_down[i-1][j].second) {
                        suf_down[i][j].second = suf[i][j];
                    }
                }
            }
            for (int i = n; i >= 1; --i) {
                if (pre[i][j] > pre_up[i+1][j].first) {
                    pre_up_pos[i][j] = i;
                    pre_up[i][j].second = pre_up[i+1][j].first;
                    pre_up[i][j].first = pre[i][j];
                }
                else {
                    pre_up[i][j] = pre_up[i+1][j];
                    pre_up_pos[i][j] = pre_up_pos[i+1][j];
                    if (pre[i][j] > pre_up[i+1][j].second) {
                        pre_up[i][j].second = pre[i][j];
                    }
                }
                if (suf[i][j] > suf_up[i+1][j].first) {
                    suf_up_pos[i][j] = i;
                    suf_up[i][j].second = suf_up[i+1][j].first;
                    suf_up[i][j].first = suf[i][j];
                }
                else {
                    suf_up[i][j] = suf_up[i+1][j];
                    suf_up_pos[i][j] = suf_up_pos[i+1][j];
                    if (suf[i][j] > suf_up[i+1][j].second) {
                        suf_up[i][j].second = suf[i][j];
                    }
                }
            }
        }
        ll ans = 1ll * board[0][0] + board[1][1] + board[2][2];
        for (int i = 1; i <= n; ++i) {
            for (int j = 2; j <= m-1; ++j) {
                // 中间列元素
                ll mx = 3ll * -inf;
                if (i >= 2 && i <= n-1) {
                    mx = max(mx, max(pre_down[i-1][j-1].first + suf_up[i+1][j+1].first, pre_up[i+1][j-1].first + suf_down[i-1][j+1].first));
                }
                if (i >= 3) {
                    if (pre_down_pos[i-1][j-1] != suf_down_pos[i-1][j+1]) mx = max(mx, pre_down[i-1][j-1].first + suf_down[i-1][j+1].first);
                    else mx = max(mx, max(pre_down[i-1][j-1].first + suf_down[i-1][j+1].second, pre_down[i-1][j-1].second + suf_down[i-1][j+1].first));
                }
                if (i <= n-2) {
                    if (pre_up_pos[i+1][j-1] != suf_up_pos[i+1][j+1]) mx = max(mx, pre_up[i+1][j-1].first + suf_up[i+1][j+1].first);
                    else mx = max(mx, max(pre_up[i+1][j-1].first + suf_up[i+1][j+1].second, pre_up[i+1][j-1].second + suf_up[i+1][j+1].first));
                }
                ans = max(ans, mx+board[i-1][j-1]);
            }
        }
        return ans;
    }
};