#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        int m = grid[0].size();
        vector<ll> suf(m + 2), pre(m + 1);
        for (int i = 0; i < m; ++i) {
            pre[i + 1] = pre[i] + grid[1][i];
        }
        for (int i = m; i >= 1; --i) {
            suf[i] = suf[i + 1] + grid[0][i - 1];
        }
        ll ans = llinf;
        for (int i = 0; i <= m - 1; ++i) {
            ll res = max(pre[i], suf[i + 2]);
            ans = min(ans, res);
        }
        return ans;
    }
};