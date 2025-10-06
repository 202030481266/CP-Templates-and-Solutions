#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 200005;

int sum[MAXN];

void solve() {
    int l, r;
    cin >> l >> r;
    int x = l, ans = 0;
    while (x) {
        ++ans;
        x /= 3;
    }
    ans *= 2;
    ans += sum[r] - sum[l];
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int i = 1, x; i <= 200000; ++i) {
        x = i;
        while (x) {
            ++sum[i];
            x /= 3;
        }
        sum[i] += sum[i - 1];
    }
    while (t--) solve();
}