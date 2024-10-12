#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const long long POWERS_OF_10[] = {
    1LL,                      // 10^0
    10LL,                     // 10^1
    100LL,                    // 10^2
    1000LL,                   // 10^3
    10000LL,                  // 10^4
    100000LL,                 // 10^5
    1000000LL,                // 10^6
    10000000LL,               // 10^7
    100000000LL,              // 10^8
    1000000000LL,             // 10^9
    10000000000LL             // 10^10
};

class Solution {
public:
    int findInteger(int k, int a, int b) {
        ll ans = INT_MAX;

        function<void(int,bool, ll, int)> dfs = [&](int p, bool is_num, ll cur, int r) {
            if (p < 0) {
                if (is_num && r == 0 && cur > k && cur <= INT_MAX) {
                    ans = min(ans, cur);
                }
                return;
            }
            // no choose
            if (!is_num) {
                dfs(p-1, false, cur, r);
            }
            // choose
            for (int i : {a, b}) {
                dfs(p-1, true, cur + i * POWERS_OF_10[p], (r + i * POWERS_OF_10[p] % k) % k);
            }
        };
        dfs(9, false, 0, 0);
        return (ans == INT_MAX ? -1 : ans);
    }
};