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

/*
1
8
49
288
1681
9800
57121
332928
*/

static constexpr int bad[] = { 1, 8, 49, 288, 1681, 9800, 57121, 332928 };

bool isBad(int x) {
    for (int i = 0; i < 8; ++i) {
        if (x == bad[i]) return true;
    }
    return false;
}

void solve() {
    int n;
    cin >> n;
    if (isBad(n)) {
        cout << -1 << '\n';
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (isBad(i)) {
            cout << i + 1 << ' ' << i << ' ';
            ++i;
        }
        else cout << i << ' ';
    }
    cout << '\n';
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