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
    int n;
    cin >> n;
    cout << ((1 << n) - 1) << ' ' << ((1 << n - 1) - 1) << ' ';
    for (int k = n - 2, j = 1, x = 0; k >= 0; --k, ++j) {
        int suf = (1 << k) - 1;
        for (int i = 0; i < 1 << j; ++i) {
            cout << ((x << k + 1) + suf) << ' ';
            ++x;
        }
        x = 0;
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