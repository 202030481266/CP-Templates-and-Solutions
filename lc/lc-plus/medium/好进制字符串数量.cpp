#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

const int maxn = 100010;
long long fac[maxn], ifac[maxn];

long long quick_power(long long a, long long b, int p) { 
    long long ans = 1 % p;
    for(; b; b >>= 1) {
        if(b & 1) ans = ans * a % p;
        a = a * a % p;
    }
    return ans;
}
long long inv(long long x, int p = mod) {
    return quick_power(x, p - 2, p) % mod;
}
long long binomial(int x, int y) {
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
bool flag = false;

void init(int n) {
    if (flag) return;
    flag = true;
    fac[0] = 1;
    int N = 100000;
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[N] = inv(fac[N]);
    for (int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}


// 首先是组合数的计算公式
// C(n+1,k+1) = C(n, k+1) + C(n,k)
// C(n+1, k+1) = C(n-1,k+1) + C(n-1, k) + C(n, k)
// 继续展开可得：
// C(n+1, k+1) = C(n-2,k+1) + C(n-2,k) + C(n-1,k) + C(n,k)
// 最终可以表示为：
// C(n+1, k+1) = C(k+1,k+1) + C(k+2, k) + ... C(n,k)

int floor(int val, int div) {
    return (val-1) / div + 1;
}

class Solution {
public:
    int goodBinaryStrings(int minl, int maxl, int one, int zero) {
        // 初始化组合数
        init(maxl);
        // n = x * one + y * zero
        // (x, y)， C (x + y, x)
        ll ans = 0;
        for (int i = 0; i <= maxl / one; ++i) {
            // x * one + y * zero 
            int mn = floor(max(0,minl-i*one), zero), mx = (maxl-i*one)/zero;
            // then we should calculate the combination numbers
            // C(mn+x, x) + C(mn+1+x, x) + ... C(mx+x,x) = C(x+mx+1,x+1) - C(mn+x,x+1)
            if (mn > 0)
                ans = (ans + binomial(i+mx+1, i+1) - binomial(mn+i, i+1) + mod) % mod;
            else
                ans = (ans + binomial(i+mx+1, i+1)) % mod;
        }
        return ans;
    }
};

// 动态规划做法
// 看起来还是动态规划好使啊，数学真的是给自己上难度，不过更加明显的实数学方法常数小得多

const int MODULO = 1000000007;

class Solution {
public:
    int goodBinaryStrings(int minLength, int maxLength, int oneGroup, int zeroGroup) {
        vector<int> dp(maxLength + 1);
        dp[0] = 1;
        for (int i = 1; i <= maxLength; i++) {
            if (i >= oneGroup) {
                dp[i] = (dp[i] + dp[i - oneGroup]) % MODULO;
            }
            if (i >= zeroGroup) {
                dp[i] = (dp[i] + dp[i - zeroGroup]) % MODULO;
            }
        }
        int total = 0;
        for (int i = minLength; i <= maxLength; i++) {
            total = (total + dp[i]) % MODULO;
        }
        return total;
    }
};
