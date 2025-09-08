#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int dp[51], flag = 1;

void init() {
    flag = 0;
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= 50; ++i) {
        dp[i] = (1 << ((i - 1) / 2));
    }
}

class Solution {
public:
    int countBinaryPalindromes(long long N) {
        if (flag) init();
        if (N <= 1) return N + 1;
        ull n = (ull)N;
        int m = bit_width(n), ans = 0;
        ull cur = (1ull << (m - 1)) + 1, j;
        for (int i = 0; i < m; ++i) {
            ans += dp[i];
        }
        for (int i = m - 2; i >= m / 2; --i) {
            j = (n >> i) & 1;
            if (j) {
                // (i, m / 2] can be choose arbitrarily 
                ans += (1ull << (i - m / 2));
            }
            cur |= (j << i);
        }
        for (int i = m / 2 - 1; i >= 0; --i) {
            if ((cur >> (m - 1 - i)) & 1) cur |= (1ull << i);
        }
        return ans + (cur <= n);
    }
};