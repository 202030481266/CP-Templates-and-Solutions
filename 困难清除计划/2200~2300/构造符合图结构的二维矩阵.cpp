#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        // 这道题主要是实现细节多
        vector<int> cnt(n);
        vector<int> g[n];
        for (auto e : edges) {
            cnt[e[0]]++;
            cnt[e[1]]++;
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        int mn = inf, mx = -inf;
        for (int i = 0; i < n; ++i) {
            mn = min(mn, cnt[i]);
            mx = max(mx, cnt[i]);
        }
        
        if (mn == 1) {
            // 一行或者一列
            int start = 0;
            for (int i = 0; i < n; ++i) {
                if (cnt[i] == 1) {
                    start = i;
                    break;
                }
            }
            vector ans(1, vector<int>(n));
            for (int i = 0; i < n; ++i) {
                ans[0][i] = start;
                if (i == n-1) break;
                if (i == 0) start = g[start][0];
                else {
                    if (g[start][0] == ans[0][i-1]) start = g[start][1];
                    else start = g[start][0];
                }
            }
            return ans;
        }

        auto check = [&](int val, int t) -> bool {
            for (int adj : g[t])
                if (adj == val) return true;
            return false;
        };

        vector<bool> vis(n, false);

        // 最多就是3
        if (mx == 3) {
            vector<int> tmp;
            for (int i = 0; i < n; ++i) {
                if (cnt[i] == 2) {
                    tmp.push_back(i);
                }
            }
            int left_up = tmp[0], adj = -1;
            for (int i = 1; i < tmp.size(); ++i) {
                if (check(tmp[i], left_up)) {
                    adj = tmp[i];
                    break;
                }
            }
            // left_up, adj
            vector<int> x{left_up}, y{adj};
            vis[left_up] = vis[adj] = true;
            while (true) {
                int next1 = -1, next2 = -1;
                for (int v : g[left_up]) {
                    if (!vis[v]) {
                        next1 = v;
                        break;
                    }
                }
                for (int v : g[adj]) {
                    if (!vis[v]) {
                        next2 = v;
                        break;
                    }
                }
                if (next1 == -1 || next2 == -1) break;
                x.push_back(next1);
                y.push_back(next2);
                vis[next1] = vis[next2] = true;
                left_up = next1;
                adj = next2;
            }
            vector<vector<int>> ans(2);
            ans[0] = x;
            ans[1] = y;
            return ans;
        }

        // 存在一个四的节点

        // 寻找左上角
        int left_up = 0;
        for (int i = 0; i < n; ++i) {
            if (cnt[i] == 2) {
                left_up = i;
                break;
            }
        }
        // 右边
        int right = g[left_up][0], down = g[left_up][1];
        vector<int> y{left_up}, x{left_up};
        vis[left_up] = true;
        while (true) {
            int next = -1;
            y.push_back(right);
            vis[right] = true;
            if (cnt[right] == 2) break;
            // [0,m-1]
            for (int v : g[right]) {
                if (cnt[v] <= 3 && !vis[v]) {
                    next = v;
                    break;
                }
            }
            if (next == -1) break;
            right = next;
        }
        while (true) {
            int next = -1;
            x.push_back(down);
            vis[down] = true;
            if (cnt[down] == 2) break;
            // [0,n-1]
            for (int v : g[down]) {
                if (cnt[v] <= 3 && !vis[v]) {
                    next = v;
                    break;
                }
            }
            if (next == -1) break;
            down = next;
        }
        int N = x.size(), M = y.size();
        vector ans(N, vector<int>(M));
        for (int i = 0; i < M; ++i) ans[0][i] = y[i];
        for (int i = 0; i < N; ++i) ans[i][0] = x[i];
        for (int i = 1; i < N; ++i) {
            for (int j = 1; j < M; ++j) {
                int u = ans[i-1][j], v = ans[i][j-1];
                for (int adj : g[u]) {
                    if (!vis[adj] && check(adj, v)) {
                        ans[i][j] = adj;
                        vis[adj] = true;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};
