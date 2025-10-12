#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

// 非分类讨论的纯hash解法

class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        unordered_map<ll, int> pos; // abc, ab, ac, bc, a, b, c
        pos.reserve(n * 10);
        for (ll i = 1; i < 8; ++i) pos[i << 60] = 0; 
        ll sa = 0, sb = 0, sc = 0;
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (s[i-1] == 'a') ++sa;
            if (s[i-1] == 'b') ++sb;
            if (s[i-1] == 'c') ++sc;
            ll y = 0, x = 0;
            if (sa) x |= 4, y |= sa << 40;
            if (sb) x |= 2, y |= sb << 20;
            if (sc) x |= 1, y |= sc;
            for (ll j = 1, mn = inf, t = 0; j < 8; ++j, mn = inf, t = 0) {
                if ((j & x) == j) {
                    for (int k = 0; k < 3; ++k) {
                        if (j >> k & 1) mn = min(mn, (y >> k * 20) & (1 << 20) - 1);
                    }
                    t |= j << 60;
                    for (int k = 0; k < 3; ++k) {
                        if (j >> k & 1) t |= (((y >> k * 20) & (1 << 20) - 1) - mn) << k * 20;
                        else t |= ((y >> k * 20) & (1 << 20) - 1) << k * 20;
                    }
                }
                else t |= j << 60 | y;
                if (!pos.count(t)) pos[t] = i;
                else ans = max(ans, i - pos[t]);
            }
        }
        return ans;
    }
};