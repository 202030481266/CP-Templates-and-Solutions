#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;



class Solution {
public:
    long long minCost(string s, int encCost, int flatCost) {
        int n = s.size();
        vl sum(n + 1);
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + s[i] - '0';
        }
        if (n & 1) {
            return sum[n] == 0 ? flatCost : n * sum[n] * encCost;
        }
        int x = n;
        while (x % 2 == 0) x /= 2;
        vl f(n + 1);
        for (int len = x; len <= n; len <<= 1) {
            for (int i = 1; i <= n; i += len) {
                ll ones = sum[i + len - 1] - sum[i - 1];
                ll cost = ones == 0 ? flatCost : len * ones * encCost;
                if (len >= 2 && len % 2 == 0) {
                    f[i] = min(cost, f[i] + f[i + len / 2]);
                }
                else f[i] = cost;
            }
        }
        return f[1];
    }
};