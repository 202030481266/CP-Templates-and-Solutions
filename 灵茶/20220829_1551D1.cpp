#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int INF = 0x3f3f3f3f;

int n, m, k;
int ans[200][200];

void solve() {
    cin >> n >> m >> k;
    if (m / 2 * n < k) {
        cout << "NO\n";
        return;
    }
    if (n % 2 == 0) {
        if (k % 2 == 0) cout << "YES\n";
        else cout << "NO\n";
    }
    else {
        if (m % 2 == 0) {
            int x = m / 2;
            if (k >= x && (k - x) % 2 == 0) cout << "YES\n";
            else cout << "NO\n";
        }
        else cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) solve();
}

