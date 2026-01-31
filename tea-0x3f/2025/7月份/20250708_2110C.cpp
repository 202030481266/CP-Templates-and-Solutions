#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 200005;

// 差分约束
// 尝试不使用图的做法

int n;
int d[maxn], b[maxn], c[maxn];
array<int, 2> a[maxn];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> d[i];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1];
    }
    int l = 0, r = 0;
    for (int i = 1; i <= n; ++i) { // left -> right
        if (d[i] == 0) {
            l = max(l, a[i][0]);
            r = min(r, a[i][1]);
        }
        else if (d[i] == 1) {
            l = max(l + 1, a[i][0]);
            r = min(r + 1, a[i][1]);
        }
        else {
            l = max(l, a[i][0]);
            r = min(r + 1, a[i][1]);
        }
        if (r < l) {
            cout << -1 << '\n';
            return;
        }
        b[i] = r;
        c[i] = l;
    }
    for (int i = n - 1; i >= 0; --i) { // right -> left
        if (d[i + 1] == 0) {
        	b[i] = min(b[i], b[i+1]);
        	c[i] = max(c[i], c[i+1]);
        }
        else if (d[i + 1] == 1) {
        	b[i] = min(b[i], b[i+1] - 1);
        	c[i] = max(c[i], c[i+1] - 1);
        }
        else {
        	b[i] = min(b[i], b[i+1]);
        	c[i] = max(c[i], c[i+1] - 1);
        }
        if (b[i] < c[i]) {
            cout << -1 << '\n';
            return;
        }
    }
    for (int i = 1; i <= n; ++i) { // greedy
        if (d[i] == 1) {
            b[i] = b[i-1] + 1;
        }
        else if (d[i] == 0) {
            b[i] = b[i-1];
        }
        else {
            if (b[i-1] < b[i]) {
                b[i] = b[i-1] + 1;
                d[i] = 1;
            }
            else {
                b[i] = b[i-1];
                d[i] = 0;
            }
        }
        if (b[i] < c[i]) {
            cout << -1 << '\n';
            return;
        }
    }
    for (int i = 1; i <= n; ++i) cout << d[i] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}