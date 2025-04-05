#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    long long minEliminationTime(vector<int>& timeReq, int splitTime) {
        int n = timeReq.size();
        if (n == 1) return timeReq[0];
        sort(timeReq.begin(), timeReq.end(), greater<int>());
        
        auto check = [&](ll val) -> bool {
            ll cur = 1;
            int i = 0;
            for (; i < n && cur > 0; ++i) {
                ll x = val - timeReq[i];
                ll tot = x / splitTime;
                if (tot >= 20) return true; // so many!
                cur *= (1 << tot); // 繁殖
                if (cur >= (n - i)) return true;
                if (cur == 0) return false;
                --cur;
                val -= tot * splitTime;
            }
            return i == n;
        };
        
        ll l = timeReq[0], r = 1ll * splitTime * (n - 1) + timeReq[0] + 1;
        while (l + 1 < r) {
            ll mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid;
        }
        return r;
    }
};