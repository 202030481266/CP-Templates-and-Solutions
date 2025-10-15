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

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cin >> n;
        cout << n << '\n';
        return;
    }
    vi a(n + 1);
    vi x(n + 1), y(n + 1);
    ll sum = 0, ans = (n & 1 ? n - 1 : n - 2);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (i & 1) {
            sum += a[i];
            x[i] = i + 2 * a[i];
            if (i > 1) {
                x[i] = min(x[i], x[i - 2]);
                ans = max(ans, 1ll * i - 2 * a[i] - y[i - 1]);
            }
        }
        else {
            sum -= a[i];
            y[i] = i - 2 * a[i];
            if (i > 1) {
                y[i] = min(y[i], y[i - 2]);
                ans = max(ans, 1ll * i + 2 * a[i] - x[i - 1]);
            }
        }
    }
    cout << (sum + ans) << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
