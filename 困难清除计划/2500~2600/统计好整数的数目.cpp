#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 找出最大的 N 位 K 回文数, https://leetcode.cn/problems/find-the-largest-palindrome-divisible-by-k/description/
// 感觉上面这道题目有关系，并且上面这道题目难很多吧

int p[10][11], flag = 0; 
ll cache[11][11];
const int fac[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

void init() {
    if (flag) return;
    flag = 1;
    memset(cache, -1, sizeof(cache)); // 初始化-1，只会运行一遍
    for (int k = 1; k <= 9; ++k) {
        p[k][0] = 1 % k;
        for (int i = 1; i < 11; ++i) { // 最多10位数数字， 0~9
            // 10^x % mod = 10^(x-1) * 10 % mod = 10^(x-1) % mod * 10 % mod
            p[k][i] = p[k][i-1] * 10 % k;
        }
    }
}

ll ans, N, K;
int cnt[10];

unordered_set<ll> vis; // 因为会存在重复计算的场景（因为枚举的回文构成，而不是按照数位信息枚举的）

ll cal() {
    // 计算cnt里面的数据
    ll s = 0, res = fac[N], div = 1;
    for (int i = 0; i < 10; ++i) {
        if (cnt[i]) div *= fac[cnt[i]];
        s |= (ll)(cnt[i]) << (4*i);
    }
    if (vis.count(s)) {
        return 0;
    }
    vis.insert(s);
    res /= div;
    if (cnt[0]) {
        // 除去前导零的影响
        // 0 _ _ _
        ll x = fac[N-1], tmp = fac[cnt[0]-1];
        for (int i = 1; i < 10; ++i)
            if (cnt[i]) tmp *= fac[cnt[i]];
        res -= x / tmp;
    }
    return res;
}

void dfs(int pos, ll sum) {
    if (pos == (N-1)/2+1) {
        if (sum % K == 0)
            ans += cal();
        return;
    }
    bool flag = (N & 1) && (pos == N / 2);
    for (int i = (pos == 0 ? 1 : 0); i < 10; ++i) {
        cnt[i] += (flag ? 1 : 2);
        dfs(pos + 1, (sum + (flag ? i * p[K][N/2] : i * (p[K][pos] + p[K][N-1-pos]))) % K);
        cnt[i] -= (flag ? 1 : 2);
    }
}

class Solution {
public:
    long long countGoodIntegers(int n, int k) {
        init();
        if (cache[n][k] != -1) return cache[n][k];
        ans = 0, N = n, K = k;
        vis.clear();
        dfs(0, 0);
        return cache[n][k] = ans;
    }
};