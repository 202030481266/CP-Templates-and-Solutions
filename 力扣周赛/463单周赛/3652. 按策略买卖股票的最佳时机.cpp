#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        ll res = 0, delta = 0, ans = 0;
        for (int i = 0; i < n; ++i) res += 1ll * prices[i] * strategy[i];
        for (int i = 0; i < k / 2; ++i) {
            delta -= prices[i] * strategy[i];
        }
        for (int i = k / 2; i < k; ++i) {
            delta += (1 - strategy[i]) * prices[i];
        }
        ans = max(ans, delta);
        for (int i = k / 2; i + k / 2 < n; ++i) {
            delta -= (1 - strategy[i]) * prices[i];
            delta -= prices[i] * strategy[i];
            delta += prices[i - k / 2] * strategy[i - k / 2];
            delta += (1 - strategy[i + k / 2]) * prices[i + k / 2];
            ans = max(ans, delta);
        }
        return res + ans;
    }
};
