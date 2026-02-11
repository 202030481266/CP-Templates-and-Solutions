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

void solve() {
    int n, m;
    cin >> n >> m;
    vii a(n, vi(m));
    vi row(n * m + 1);
    vi col(n * m + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            row[a[i][j]] = i;
            col[a[i][j]] = j;
        }
    }
    vii b(n, vi(m));
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> b[i][j];
    }
    for (int i = 0; i < n && flag; ++i) {
        int r = row[b[i][0]];
        for (int j = 1; j < m && flag; ++j) {
            if (row[b[i][j]] != r) flag = false;
        }
    }
    for (int i = 0; i < m && flag; ++i) {
        int c = col[b[0][i]];
        for (int j = 1; j < n && flag; ++j) {
            if (col[b[j][i]] != c) flag = false;
        }
    }
    if (flag) cout << "YES\n";
    else cout << "NO\n";
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