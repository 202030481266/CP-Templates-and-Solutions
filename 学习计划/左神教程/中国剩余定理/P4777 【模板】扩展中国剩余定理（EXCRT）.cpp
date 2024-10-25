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

// 扩展中国剩余定理求解，给定一组同余方程 x ≡ r_i (mod m_i)，求 x 的最小正整数解
ll extendedChineseRemainderTheorem(const vector<ll>& residues, const vector<ll>& moduli) {
    int n = residues.size();
    ll lcm = 1; // 当前的最小公倍数
    ll tail = 0; // 当前的偏移量

    for (int i = 0; i < n; ++i) {
        ll a = lcm;
        ll b = moduli[i];
        ll c = residues[i] - tail;
        ll x, y;
        ll gcd = extendedGCD(a, b, x, y);

        if (c % gcd != 0) {
            // 如果 c 不是 gcd 的倍数，则无解
            return -1;
        }

        // 计算最小非负解
        x = quick_mul(x, c / gcd, b / gcd);
        auto tmp = lcm * (b / gcd); // 更新最小公倍数
        tail = (quick_mul(x, lcm, tmp) + tail) % tmp;
        lcm = tmp;
    }

    // 保证 tail 是最小正整数解
    return (tail + lcm) % lcm;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> residues(n); // 余数数组
    vector<ll> moduli(n);   // 模数数组

    for (int i = 0; i < n; ++i) cin >> moduli[i] >> residues[i];

    // 调用中国剩余定理函数求解
    ll result = extendedChineseRemainderTheorem(residues, moduli);
    cout << result << endl;

    return 0;
}