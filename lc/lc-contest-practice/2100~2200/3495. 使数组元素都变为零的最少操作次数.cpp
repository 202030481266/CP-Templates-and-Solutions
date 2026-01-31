#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        ll ans = 0;
        for (auto q : queries) {
            ll l = q[0], r = q[1], sum = 0, cur = r, mx = -1;
            for (int i = 31; i >= 0 && cur >= l; --i) {
                if ((1ll << i) <= cur) {
                    // [1<<i, cur]
                    int x = (i + 2) / 2;
                    ll left = max(l, (1ll << i));
                    sum += (cur - left + 1) * x;
                    if (mx == -1) {
                        mx = x;
                    }
                    cur = left - 1;
                }
            }
            if (sum - mx < mx) ans += mx;
            else {
                if (sum % 2 == 0) ans += sum / 2;
                else ans += sum / 2 + 1;
            }
        }
        return ans;
    }
};