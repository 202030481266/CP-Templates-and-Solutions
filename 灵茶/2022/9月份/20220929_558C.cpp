// Problem: C. Amr and Chemistry
// Contest: Codeforces - Codeforces Round 312 (Div. 2)
// URL: https://codeforces.com/problemset/problem/558/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int n, arr[MAXN], b[MAXN], use[MAXN];

void solve() {
    cin >> n;
    if (n == 1) {
        cout << 0 << '\n';
        return;
    }
    int ans = INF, cnt = n, pre, cost = 0, mn = 18, last = 0;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    for (int iter = 0; iter < 18 && cnt > 0; ++iter) { // max iters
        mn = 18;
        // calculate the common prefix
        for (int i = 0; i < n; ++i) {
            b[i] = bit_width(1u * arr[i]);
            if (use[i]) continue;
            mn = min(mn, b[i]);
        }
        int _and = (1 << mn) - 1, _or = 0;
        for (int i = 0; i < n; ++i) {
            if (use[i]) continue;
            _and &= (arr[i] >> b[i] - mn);
            _or |= (arr[i] >> b[i] - mn);
        }
        pre = mn - bit_width(static_cast<unsigned int>(_and ^ _or));
        if (last == 0) last = pre;
        while (last < pre && (_or >> mn - last - 1 & 1) == 0) ++last; // we should stop at the 1 position
        int res = 0;
        for (int i = 0; i < n; ++i) res += abs(last - b[i]);
        ans = min(ans, res + cost);
        for (int i = 0; i < n; ++i) {
            if (use[i]) continue;
            if (((arr[i] >> b[i] - last - 1) & 1) || (b[i] == last)) {
                --cnt;
                use[i] = 1;
                arr[i] >>= (b[i] - last);
                cost += b[i] - last;
            }
        }
    }
    // last calculate
    for (int i = 0; i < n; ++i) {
        b[i] = bit_width(1u * arr[i]);
        cost += last - b[i];
    }
    ans = min(ans, cost);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}