#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)


void solve() {
    int n, k;
    int final_mex = 0;
    int cur_mex = 0;
    ll sum = 0;
    cin >> n >> k;
    vector<int> cnt(n + 1);
    for (int i = 0, v; i < n; ++i) {
        cin >> v;
        cnt[v]++;
        sum += v;
    }
    for (int i = 0; i <= n; ++i) { // n + 1 element, at least one is empty
        if (cnt[i] == 0 || cnt[i] > 1) {
            final_mex = i;
            break;
        }
    }
    for (int i = 0; i <= n; ++i) {
        if (!cnt[i]) {
            cur_mex = i;
            break;
        }
    }
    int tot = 0;
    ll res = 0;
    for (int i = 0; i <= n; ++i) {
        if (cnt[i] > 1 || i > cur_mex) {
            tot += cnt[i];
            res += (cur_mex - i) * cnt[i];
        }
    }
    if (tot == 0) { // won't change anymore
        cout << sum << '\n';
        return;
    }
    if (tot == 1) { // 0, 1, 2, .. cur_mex, .. mx_value
        // 0.... cur_mex
        cout << (1ll * (cur_mex + 1) * cur_mex / 2) << '\n';
        return;
    }
    // otherwise all the element will become final_mex
    // if cur_mex == final_mex, at first turn
    // else at second turn
    if (k == 1) {
        cout << sum + res << '\n';
        return;
    }
    if (final_mex != cur_mex) --k;
    if (k & 1) {
        // 0, 1, 2, ... final_mex - 1, final_mex * (n - finale_mex)
        sum = 1ll * final_mex * (final_mex - 1) / 2 + 1ll * final_mex * (n - final_mex);
    }
    else {
        // 0, 1, 2, ... finale_mex - 1, (final_mex + 1) * (n - final_mex);
        sum = 1ll * final_mex * (final_mex - 1) / 2 + 1ll * (final_mex + 1) * (n - final_mex);
    }
    cout << sum << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}