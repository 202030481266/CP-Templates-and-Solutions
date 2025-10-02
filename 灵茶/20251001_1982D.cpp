#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 1003;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

int a[505][505];
int b[505][505];
int n, m, k;

void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> a[i][j];
    }
    char t;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> t;
            if (t == '0') b[i][j] = 0;
            else b[i][j] = 1;
        }
    }
    ll s0 = 0, s1 = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (b[i][j]) s1 += a[i][j];
            else s0 += a[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
    }
    int g = 0;
    for (int i = 1; i + k - 1 <= n; ++i) {
        for (int j = 1; j + k - 1 <= m; ++j) {
            int s = b[i + k - 1][j + k - 1] - b[i + k - 1][j - 1] - b[i - 1][j + k - 1] + b[i - 1][j - 1];
            s = abs(k * k - s * 2);
            g = gcd(g, s);
        }
    }
    if (s0 - s1 == 0 || g > 0 && (s0 - s1) % g == 0) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}