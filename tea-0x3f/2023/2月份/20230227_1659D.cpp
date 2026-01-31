#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;


void solve() {
    int n;
    cin >> n;
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    // once a[i] appeared as 0, after then it will always be 0
    // at the sorted array, once a[i] is 1, then right of it all is 1
    int last = 0, p = 1;
    vi first(n + 1);
    vi ans(n + 1);
    while (p <= n && arr[p] == 0) ++p;
    if (p <= n) {
        for (int i = p; i <= n; ++i) first[i] = i - 1;
        for (int i = p; i <= n; ++i) {
            int ones = i - first[i];
            if (ones > last) ans[i] = 1;
            int x = arr[i] - ans[i] * (i - 1) - 1;
            while (p <= min(n, x + i)) {
                first[p] = i - 1;
                ++p;
            }
            last = ones;
        }
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    cout << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
