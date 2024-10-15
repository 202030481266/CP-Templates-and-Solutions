#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'


// 周期 T = (2^k-1) / (N+1), k 是 2 在模 n 下的乘法阶
// 2^M * x - y * N + 2^M - 1 - y = L - 1
// 2^M * x - y * (N+1) = L - 2^M
// 2^M * x = (L - 2^M) % (N+1) mod (N+1)

// must use __int128 to avoid the overflow or use the 光速乘
ll mod_mul(ll a, ll b, ll mod) {
    return ((__int128)a * b) % mod;
}

ll pow_mod(ll a, ll b, ll mod) {
    ll res = 1 % mod;
    a %= mod;
    while (b) {
        if (b & 1) res = mod_mul(res, a, mod);
        a = mod_mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = extended_gcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

ll modinv(ll a, ll m) {
    ll x, y;
    ll g = extended_gcd(a, m, x, y);
    if (g != 1) {
        // Inverse doesn't exist
        return -1;
    } else {
        return (x % m + m) % m;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N, M, L;
    cin >> N >> M >> L;

    N++; // Increment N to N+1 for modulus
    ll A = pow_mod(2, M, N);
    ll B = (L - A + N) % N;

    // Compute the modular inverse of A modulo N
    ll inv_A = modinv(A, N);
    if (inv_A == -1) {
        cout << "Inverse doesn't exist" << endl;
        return 0;
    }

    ll x = mod_mul(B, inv_A, N);
    if (x == 0) x = N; // Adjust if x is 0

    cout << x+1 << endl;

    return 0;
}