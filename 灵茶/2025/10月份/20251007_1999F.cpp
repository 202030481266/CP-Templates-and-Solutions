#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

long long fac[MAXN], ifac[MAXN];

long long quick_power(long long a, long long b, int p) {
    long long ans = 1 % p;
    for(; b; b >>= 1) {
        if(b & 1) ans = ans * a % p;
        a = a * a % p;
    }
    return ans;
}
long long inv(long long x, int p = MOD) {
    return quick_power(x, p - 2, p) % MOD;
}
long long binomial(int x, int y) {
    return fac[x] * ifac[y] % MOD * ifac[x - y] % MOD;
}

void init() {
    int n = 200000;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[n] = inv(fac[n]);
    for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
}

int n, k;
void solve() {
    cin >> n >> k;
    int m = (k + 1) / 2, sum = 0;
    for (int i = 0, t; i < n; ++i) {
        cin >> t;
        sum += t;
    }
    if (sum < m) {
        cout << 0 << '\n';
        return;
    }
    ll ans = 0;
    for (int i = max(k + sum - n, m); i <= min(k, sum); ++i) {
        // k - i <= n - sum -> i >= k + sum - n
        ans = (ans + binomial(sum, i) * binomial(n - sum, k - i) % MOD) % MOD;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    init();
    while (t--) solve();
}