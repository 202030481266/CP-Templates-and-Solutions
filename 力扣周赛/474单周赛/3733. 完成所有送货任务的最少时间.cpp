#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    long long minimumTime(vector<int>& d, vector<int>& r) {
        ll vl = 0, vr = 1ll * d[0] * r[0] + 1ll * d[1] * r[1];
        auto check = [&](ll tim) -> bool {
            ll x = tim / r[0], y = tim / r[1], z = tim / lcm(r[0], r[1]);
            x -= z;
            y -= z;
            ll a = max(0ll, d[0] - y), b = max(0ll, d[1] - x);
            return a + b <= tim - x - y - z;
        };
        while (vl + 1 < vr) {
            ll mid = (vl + vr) / 2;
            if (check(mid)) vr = mid;
            else vl = mid;
        }
        return vr;
    }
};