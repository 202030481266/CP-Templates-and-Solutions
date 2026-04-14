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

const long long INV_9 = 111111112;

long long fastPow(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long geometricSum(long long a, long long n) {
    if (n == 0) return 0;
    long long q_pow_n = fastPow(10, n);
    long long term = (q_pow_n - 1 + MOD) % MOD;
    long long res = (a % MOD * term) % MOD;
    res = (res * INV_9) % MOD;
    return res;
}

class Solution {
public:
    int sumOfNumbers(int l, int r, int k) {
        ll n = r - l + 1;
        ll A = (r + l) * (r - l + 1) / 2;
        return A * fastPow(n, k - 1) % MOD * geometricSum(1, k) % MOD;
    }
};