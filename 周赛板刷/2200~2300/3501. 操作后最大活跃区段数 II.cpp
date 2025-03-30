#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<pii> a;
        vector<int> ids(n), rk(n);
        int p = 0, sum = 0;
        while (p < n) {
            int i = p;
            while (i < n && s[i] == s[p]) {
                ids[i] = a.size();
                rk[i] = i-p;
                ++i;
            }
            a.push_back({s[p] - '0', i - p});
            sum += a.back().second * a.back().first;
            p = i;
        }
        int m = a.size();
        vector<int> b(m);
        for (int i = 1; i < m - 1; ++i) {
            if (a[i].first == 1) {
                b[i] = a[i-1].second + a[i+1].second;
            }
        }
        // 静态区间最大值查询
        vector st(m, vector<int>(20));
        for (int i = 0; i < m; ++i) st[i][0] = b[i];
        int t = log(m) / log(2) + 1;
        for (int i = 1; i < t; ++i) {
            for (int j = 0; j + (1 << i) - 1 < m; ++j) {
                st[j][i] = max(st[j][i-1], st[j+(1<<(i-1))][i-1]);
            }
        }
        auto f = [&](int l, int r) { // 获取区间[l,r]的最大值
            if (r < l) return 0;
            int k = log(r - l + 1) / log(2);
            return max(st[l][k], st[r - (1 << k) + 1][k]);
        };
        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            int l = queries[i][0], r = queries[i][1];
            int lv = s[l] - '0', rv = s[r] - '0';
            if (lv && rv) {
                ans[i] = f(ids[l]+1, ids[r]-1);
            }
            else if (!lv && rv) {
                ans[i] = f(ids[l]+2, ids[r]-1);
                if (ids[l] + 1 < ids[r]) {
                    ans[i] = max(ans[i], a[ids[l]+2].second + a[ids[l]].second - rk[l]);
                }
            }
            else if (lv && !rv) {
                ans[i] = f(ids[l]+1, ids[r]-2);
                if (ids[l] + 1 < ids[r]) {
                    ans[i] = max(ans[i], a[ids[r]-2].second + rk[r] + 1);
                }
            }
            else {
                ans[i] = f(ids[l]+2, ids[r]-2);
                if (ids[l] + 2 == ids[r]) {
                    ans[i] = max(ans[i], a[ids[l]].second - rk[l] + rk[r] + 1);
                }
                else if (ids[l] + 2 < ids[r]) {
                    ans[i] = max(ans[i], a[ids[l]+2].second + a[ids[l]].second - rk[l]);
                    ans[i] = max(ans[i], a[ids[r]-2].second + rk[r] + 1);
                }
            }
        }
        for (int& v : ans) v += sum;
        return ans;
    }
};