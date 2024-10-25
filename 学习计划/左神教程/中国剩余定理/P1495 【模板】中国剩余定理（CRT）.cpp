#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

typedef long long ll;

// 大整数乘法，计算 (a * b) % p，避免溢出
ll quick_mul(ll a, ll b, ll p) {
    a = (a % p + p) % p;
    b = (b % p + p) % p;
    ll ans = 0;
    for(; b; b >>= 1) {
        if(b & 1) ans = (ans + a) % p;
        a = a * 2 % p;
    }
    return ans;
}

// 扩展欧几里得算法，求 ax + by = gcd(a, b) 的解，返回 gcd(a, b) 和对应的 x, y
ll extendedGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// 计算 a 在模 m 下的逆元，即求 a * x ≡ 1 (mod m) 的 x
ll modInverse(ll a, ll m) {
    ll x, y;
    ll gcd = extendedGCD(a, m, x, y);
    if (gcd != 1) {
        // 逆元不存在
        return -1;
    }
    return (x % m + m) % m;
}

// 中国剩余定理求解，给定一组同余方程 x ≡ r_i (mod m_i)，求 x 的最小正整数解
ll chineseRemainderTheorem(const vector<ll>& residues, const vector<ll>& moduli) {
    int n = residues.size();
    ll M = 1; // 所有模数的乘积
    for (int i = 0; i < n; ++i) {
        M *= moduli[i];
    }

    ll x = 0; // 最小正整数解
    for (int i = 0; i < n; ++i) {
        ll Mi = M / moduli[i];
        ll inv = modInverse(Mi, moduli[i]);
        if (inv == -1) {
            // 如果某个逆元不存在，则无解
            return -1;
        }
        // 使用 quick_mul 函数进行大整数乘法
        ll term = quick_mul(residues[i], quick_mul(Mi, inv, M), M);
        x = (x + term) % M;
    }

    // 保证 x 是最小正整数解
    return (x + M) % M;
}

int main() {
    int n;
    cin >> n;
    vector<ll> residues(n); // 余数数组
    vector<ll> moduli(n);   // 模数数组

    for (int i = 0; i < n; ++i) cin >> moduli[i] >> residues[i];

    // 调用中国剩余定理函数求解
    ll result = chineseRemainderTheorem(residues, moduli);
    cout << result << endl;

    return 0;
}