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

map<long long, int> factorize(long long n) {
    map<long long, int> factors;
    for (int d = 2; (long long)d * d <= n; d++) {
        while (n % d == 0) {
            ++factors[d];
            n /= d;
        }
    }
    if (n > 1) {
        ++factors[n];
    }
    return factors;
}

ll quick_pow(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a;
        a = a * a;
    }
    return res;
}

void solve() {
    ll p, q;
    if (p % q) {
        cout << p << '\n';
        return;
    }
    auto factors = factorize(q);
    ll mn = p;
    for (auto [f, t] : factors) {
        int cnt = 0;
        ll cur = p;
        while (cur % f == 0) {
            ++cnt;
            cur /= f;
        }
        mn = min(mn, quick_pow(f, cnt - t + 1));
    }
    cout << p / mn << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}