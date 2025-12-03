#include <bits/stdc++.h>
using namespace std;

static constexpr int MAXN = 3000;

int n, arr[MAXN], pre[MAXN], suf[MAXN];

void solve() {
    cin >> n;
    int one = 0, two = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        if (arr[i] == 1) ++one;
        else ++two;
    }
    int ans = max(one, two);
    one = 0;
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        if (arr[i] == 2) {
            pre[i] = mx + 1;
            mx = pre[i];
        }
        else {
            ++one;
            mx = max(mx, one);
        }
    }
    two = 0;
    mx = 0;
    for (int i = n; i >= 1; --i) {
        if (arr[i] == 1) {
            suf[i] = mx + 1;
            mx = suf[i];
        }
        else {
            ++two;
            mx = max(mx, two);
        }
    }
    for (int i = 1; i <= n; ++i) pre[i] = max(pre[i - 1], pre[i]);
    for (int i = n; i >= 1; --i) suf[i] = max(suf[i + 1], suf[i]);
    ans = max(ans, pre[n]);
    ans = max(ans, suf[1]);
    for (int i = 1; i < n; ++i) ans = max(ans, pre[i] + suf[i + 1]);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
}
