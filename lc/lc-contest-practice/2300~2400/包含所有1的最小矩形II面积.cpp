#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 难点在于三个矩形，不重叠，非零
// 不妨从一个矩形，两个矩形开始过渡，得到启发，实际上就是不断二分治的过程

class Solution {
public:
    int divide2(vector<vector<int>>& g) {
        int n = g.size(), m = g[0].size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) cnt += g[i][j];
        }
        if (cnt < 2) return inf;
        // 上下切
        vector<int> x;
        vector<pii> ys;
        for (int i = 0; i < n; ++i) {
            int mn = inf, mx = -inf;
            for (int j = 0; j < m; ++j) {
                if (g[i][j]) {
                    mn = (mn == inf ? j : mn);
                    mx = j;
                }
            }
            if (mn < inf) {
                x.push_back(i);
                ys.push_back({mn,mx});
            }
        }
        int N = x.size();
        int ans = inf;
        for (int i = 0; i < N-1; ++i) {
            // x[0]~x[i] x[i+1]~x[N-1]
            int l = ys[i].first, r = ys[i].second, sum = 0;
            for (int j = i-1; j >= 0; --j) {
                l = min(l, ys[j].first);
                r = max(r, ys[j].second);
            }
            sum += (r-l+1)*(x[i]-x[0]+1);
            l = ys[i+1].first, r = ys[i+1].second;
            for (int j = i+2; j < N; ++j) {
                l = min(l, ys[j].first);
                r = max(r, ys[j].second);
            }
            sum += (r-l+1)*(x[N-1]-x[i+1]+1);
            ans = min(ans, sum);
        }
        // 左右切
        vector<int> y;
        vector<pii> xs;
        for (int i = 0; i < m; ++i) {
            int mn = inf, mx = -inf;
            for (int j = 0; j < n; ++j) {
                if (g[j][i]) {
                    mn = (mn == inf ? j : mn);
                    mx = j;
                }
            }
            if (mn < inf) {
                y.push_back(i);
                xs.push_back({mn,mx});
            }
        }
        N = y.size();
        for (int i = 0; i < N-1; ++i) {
            // y[0]~y[i] y[i+1]~y[N-1]
            int u = xs[i].first, d = xs[i].second, sum = 0;
            for (int j = i-1; j >= 0; --j) {
                u = min(u, xs[j].first);
                d = max(d, xs[j].second);
            }
            sum += (d-u+1)*(y[i]-y[0]+1);
            u = xs[i+1].first, d = xs[i+1].second;
            for (int j = i+2; j < N; ++j) {
                u = min(u, xs[j].first);
                d = max(d, xs[j].second);
            }
            sum += (d-u+1)*(y[N-1]-y[i+1]+1);
            ans = min(ans, sum);
        }
        return ans;
    }
    int minimumSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<int> x;
        vector<pii> ys;
        // 上下切
        for (int i = 0; i < n; ++i) {
            int mn = inf, mx = -inf;
            for (int j = 0; j < m; ++j) {
                if (grid[i][j]) {
                    mn = (mn == inf ? j : mn);
                    mx = j;
                }
            }
            if (mn < inf) {
                x.push_back(i);
                ys.push_back({mn,mx});
            }
        }
        int ans = inf, N = x.size();
        for (int i = 0; i < N-1; ++i) {
            // x[0]~x[i] x[i+1]~x[N-1]
            int l1 = ys[i].first, r1 = ys[i].second, l2 = ys[i+1].first, r2 = ys[i+1].second;
            for (int j = i-1; j >= 0; --j) {
                l1 = min(l1, ys[j].first);
                r1 = max(r1, ys[j].second);
            }
            for (int j = i+2; j < N; ++j) {
                l2 = min(l2, ys[j].first);
                r2 = max(r2, ys[j].second);
            }
            vector<vector<int>> t1(grid.begin()+x[i+1], grid.end());
            vector<vector<int>> t2(grid.begin()+x[0], grid.begin()+x[i+1]);
            ans = min(ans, (r1-l1+1)*(x[i]-x[0]+1) + divide2(t1));
            ans = min(ans, (r2-l2+1)*(x[N-1]-x[i+1]+1) + divide2(t2));
        }
        cout << ans <<endl;
        // 左右切
        vector<int> y;
        vector<pii> xs;
        for (int i = 0; i < m; ++i) {
            int mn = inf, mx = -inf;
            for (int j = 0; j < n; ++j) {
                if (grid[j][i]) {
                    mn = (mn == inf ? j : mn);
                    mx = j;
                }
            }
            if (mn < inf) {
                y.push_back(i);
                xs.push_back({mn,mx});
            }
        }
        N = y.size();
        for (int i = 0; i < N-1; ++i) {
            // y[0]~y[i] y[i+1]~y[N-1]
            int u1 = xs[i].first, d1 = xs[i].second, u2 = xs[i+1].first, d2 = xs[i+1].second;
            for (int j = i-1; j >= 0; --j) {
                u1 = min(u1, xs[j].first);
                d1 = max(d1, xs[j].second);
            }
            for (int j = i+2; j < N; ++j) {
                u2 = min(u2, xs[j].first);
                d2 = max(d2, xs[j].second);
            }
            vector<vector<int>> t1,t2;
            for (const auto& row : grid) {
                t1.push_back(vector<int>(row.begin()+y[i+1], row.end()));
                t2.push_back(vector<int>(row.begin()+y[0], row.begin()+y[i+1]));
            }
            ans = min(ans, (d1-u1+1)*(y[i]-y[0]+1) + divide2(t1));
            ans = min(ans, (d2-u2+1)*(y[N-1]-y[i+1]+1) + divide2(t2));
        }
        return ans;
    }
};