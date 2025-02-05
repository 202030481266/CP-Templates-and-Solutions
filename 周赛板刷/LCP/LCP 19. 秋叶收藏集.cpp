#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    int minimumOperations(string leaves) {
        int n = leaves.size();
        vector pre(2, vector<int>(n+2));
        vector suf(2, vector<int>(n+2));
        for (int i = 0; i < n; ++i) {
            pre[0][i+1] = pre[0][i] + (leaves[i] == 'r');
            pre[1][i+1] = pre[1][i] + (leaves[i] == 'y');
        }
        for (int i = n; i >= 1; --i) {
            suf[0][i] = suf[0][i+1] + (leaves[i-1] == 'r');
            suf[1][i] = suf[1][i+1] + (leaves[i-1] == 'y');
        }
        vector<int> mn(n+2, -inf);
        mn[n-1] = suf[1][n] + pre[0][n-1];
        for (int i = n-2; i >= 2; --i) {
            mn[i] = min(mn[i+1], suf[1][i+1] + pre[0][i]);
        }
        int ans = inf;
        for (int i = 2; i <= n-1; ++i) {
            ans = min(ans, mn[i] - pre[0][i-1] + pre[1][i-1]);
        }
        return ans;
    }
};