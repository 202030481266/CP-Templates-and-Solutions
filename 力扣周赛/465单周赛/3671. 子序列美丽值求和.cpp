#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 70005;

int fenwick[maxn], f[maxn], N;

inline int lowbit(int i) {
    return i & -i;
}

void update(int p, int val) {
    while (p <= N) {
        fenwick[p] = (fenwick[p] + val) % mod;
        p += lowbit(p);
    }
}

int sum(int p) {
    int res = 0;
    while (p) {
        res = (res + fenwick[p]) % mod;
        p -= lowbit(p);
    }
    return res;
}

void clear(int p) {
    while (p <= N) {
        fenwick[p] = 0;
        p += lowbit(p);
    }
}

class Solution {
public:
    int totalBeauty(vector<int>& nums) {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());
        vector g(mx + 1, vector<int>{});
        for (int v : nums) {
            for (int i = 1; i * i <= v; ++i) {  // 实际上这个因数个数少的多，最多2 * 10^5 这个级别
                if (v % i == 0) {
                    int j = v / i;
                    g[i].push_back(v);
                    if (j != i) g[j].push_back(v);
                }
            }
        }
        for (int i = 1; i <= mx; ++i) {
            f[i] = 0;
            if (g[i].empty()) continue;
            N = *max_element(g[i].begin(), g[i].end());
            for (int j = 0, tmp; j < g[i].size(); ++j) {
                tmp = sum(g[i][j] - 1) + 1;
                update(g[i][j], tmp);
                f[i] = (f[i] + tmp) % mod;
            }
            for (int j = 0; j < g[i].size(); ++j) clear(g[i][j]);
        }
        int ans = 0;
        for (int i = mx; i >= 1; --i) {
            for (int j = i + i; j <= mx; j += i) { // 容斥原理
                f[i] = ((f[i] - f[j]) % mod + mod) % mod;
            }
            ans = (ans + 1ll * i * f[i] % mod) % mod;
        }
        return ans;
    }
};