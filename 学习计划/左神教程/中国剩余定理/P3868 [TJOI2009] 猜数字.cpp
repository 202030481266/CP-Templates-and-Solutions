#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef __int128 ll128;

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

// 打印 __int128 类型的数字
void print_ll128(ll128 num) {
    if (num == 0) {
        cout << 0;
        return;
    }
    bool neg = false;
    if (num < 0) {
        neg = true;
        num = -num;
    }
    string s;
    while (num > 0) {
        s += (num % 10) + '0';
        num /= 10;
    }
    if (neg) s += '-';
    reverse(s.begin(), s.end());
    cout << s;
}

// 中国剩余定理求解，给定一组同余方程 x ≡ r_i (mod m_i)，求 x 的最小正整数解
ll128 chineseRemainderTheorem(const vector<ll>& residues, const vector<ll>& moduli) {
    int n = residues.size();
    ll128 M = 1; // 所有模数的乘积
    for (int i = 0; i < n; ++i) {
        M *= moduli[i];
    }

    ll128 x = 0; // 最小正整数解
    for (int i = 0; i < n; ++i) {
        ll128 Mi = M / moduli[i];
        ll inv = modInverse(Mi % moduli[i], moduli[i]);
        if (inv == -1) {
            // 如果某个逆元不存在，则无解
            return -1;
        }
        ll128 term = (ll128)residues[i] * inv % M * Mi % M;
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

    for (auto& v : residues) cin >> v;
    for (auto& v : moduli) cin >> v;

    // 调用中国剩余定理函数求解
    ll128 result = chineseRemainderTheorem(residues, moduli);
    if (result == -1) {
        cout << -1 << endl;
    } else {
        print_ll128(result);
        cout << endl;
    }

    return 0;
}