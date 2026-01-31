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
#define vii vector<vector<int>>
#define vi vector<int>

int n;
ll k;
ll arr[105];

vii mul(const vii& A, const vii& x, int m) {
    // A.size() * x[0].size()
    vii res(A.size(), vi(x[0].size()));
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < x[0].size(); ++j) {
            for (int k = 0; k < A[0].size(); ++k) {
                // A[0].size() == x.size()
                res[i][j] = (res[i][j] + INT(1ll * A[i][k] * x[k][j] % m)) % m;
            }
        }
    }
    return res;
}

vii quick_pow(vii A, ll b, int m) {
    vii res(A.size(), vi(A.size()));
    for (int i = 0; i < A.size(); ++i) res[i][i] = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = mul(res, A, m);
        A = mul(A, A, m);
    }
    return res;
}

void solve() {
    cin >> n >> k;
    if (k == 1) {
        cout << n << '\n';
        return;
    }
    for (int i = 0; i < n; ++i) cin >> arr[i];
    vii A(n, vi(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ll x = arr[i] ^ arr[j];
            if (__builtin_popcountll(x) % 3 == 0) {
                A[i][j] = 1;
            }
        }
    }
    vii x(n, vi(1, 1)); // n * 1
    A = quick_pow(A, k - 1, MOD);
    auto res = mul(A, x, MOD);
    ll ans = 0;
    for (int i = 0; i < n; ++i) ans = (ans + res[i][0]) % MOD;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}