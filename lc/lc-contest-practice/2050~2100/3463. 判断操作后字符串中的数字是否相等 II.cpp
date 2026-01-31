#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// 辅助函数：计算 C(n, k) mod p，其中 p 是素数
long long mod_comb(long long n, long long k, long long p) {
    if (k > n) return 0;
    long long num = 1, denom = 1;
    for (long long i = 1; i <= k; ++i) {
        num = (num * (n - i + 1)) % p;
        denom = (denom * i) % p;
    }
    // 由于 p 是素数，可以用费马小定理求逆元
    long long inv_denom = 1;
    long long temp = denom;
    for (long long exp = p - 2; exp > 0; exp >>= 1) {
        if (exp & 1) inv_denom = (inv_denom * temp) % p;
        temp = (temp * temp) % p;
    }
    return (num * inv_denom) % p;
}

// Lucas 定理计算 C(n, k) mod p
long long lucas(long long n, long long k, long long p) {
    if (k == 0) return 1;
    return (mod_comb(n % p, k % p, p) * lucas(n / p, k / p, p)) % p;
}

// 主函数：计算 C(n, i) 的个位数
int solve(long long n, long long i) {
    // 步骤 1: 计算 C(n, i) mod 2
    int a = (i & n) == i ? 1 : 0;

    // 步骤 2: 计算 C(n, i) mod 5
    int b = lucas(n, i, 5);

    // 步骤 3: 根据 a 和 b 合并结果
    // 预先计算的中国剩余定理表
    int table[2][5] = {
        {0, 6, 2, 8, 4},  // a=0
        {5, 1, 7, 3, 9}   // a=1
    };

    return table[a][b];
}

// lucas原理 + CRT

class Solution {
public:
    bool hasSameDigits(string s) {
        int n = s.size();
        int sum = 0;
        for (int i = 0; i < n-1; ++i) {
            int c = s[i] - s[i+1];
            if (c < 0) c += 10;
            sum = (sum + c * solve(n-2, i) % 10) % 10;
        }
        return (sum == 0);
    }
};