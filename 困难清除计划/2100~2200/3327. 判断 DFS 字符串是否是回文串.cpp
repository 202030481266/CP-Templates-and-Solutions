#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<int> g[n];
        vector<int> siz(n), dfn(n); 
        int tot = 0;
        
        for (int i = 1; i < n; ++i) {
            g[parent[i]].push_back(i);
        }

        // dfs
        vector<char> a;
        function<int(int)> dfs = [&](int u) -> int {
            siz[u] = 1;
            for (int v : g[u]) {
                int sz = dfs(v);
                siz[u] += sz;
            }
            dfn[u] = tot++;
            a.push_back(s[u]);
            return siz[u];
        };
        dfs(0);

        // manacher
        int m = a.size();
        vector<char> b;
        b.assign(2*m+1, '#');
        for (int i = 0; i < m; ++i) b[2*i+1] = a[i];

        m = 2*m + 1;
        vector<int> d(m);
        for (int i = 0, c = 0, r = 0; i < m; ++i) {
            int len = (i < r ? min(d[2*c - i], r - i) : 1); 
            while (i - len >= 0 && i + len < m && b[i+len] == b[i-len]) ++len;
            if (i + len > r) {
                r = i + len;
                c = i;
            }
            d[i] = len;
        }

        vector<bool> ans(n);
        // ans[i] corresponds the string a[dfn[i]-siz[i]+1, dfn[i]]
        for (int i = 0; i < n; ++i) {
            int l = dfn[i] - siz[i] + 1, r = dfn[i];
            int x = 2*l + 1, y = 2*r + 1, mid = (x + y) / 2;
            ans[i] = (d[mid]-1 >= siz[i]);
        }
        return ans;
    }
};
