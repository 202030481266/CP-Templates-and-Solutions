#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 1000005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

void solve() {
    int m, n;
    cin >> m >> n;
    if (m > 1ll * n * (n - 1)) {
        cout << "NO" << '\n';
        return;
    }
    cout << "YES" << '\n';
    for (int i = 1; i < n && m; ++i) {
        int j = i + 1;
        while (m && j <= n) {
            if (m >= 2) {
                cout << i << ' ' << j << '\n';
                cout << j << ' ' << i << '\n';
                ++j;
                m -= 2;
            }
            else {
                cout << i << ' ' << j << '\n';
                --m;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
