#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int minimumSum(int n, int k) {
        vector<int> vis(k, 1);
        int tot = 0, ans = 0;
        for (int i = 1; i < k && tot < n; ++i) {
            if (vis[i]) {
                ans += i;
                ++tot;
                vis[k-i] = 0;
            }
        }
        int r = n - tot;
        // k, k+1, k+2, k+r-1
        return ans + (k+r-1+k) * r / 2;
    }
};