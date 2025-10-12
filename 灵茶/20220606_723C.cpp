#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 1000005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int &v : a) cin >> v;
    int ans = n / m, res = 0;
    vi cnt(m + 1, ans);
    vi use(n);
    for (int i = 0; i < n; ++i) {
        if (a[i] <= m && cnt[a[i]]) {
            use[i] = 1;
            cnt[a[i]]--;
        }
    }
    for (int i = 1; i <= m; ++i) res += cnt[i];
    int p = 1;
    for (int i = 0; i < n; ++i) {
        if (!use[i]) {
            while (p <= m && cnt[p] == 0) ++p;
            if (p <= m) {
                cnt[p]--;
                a[i] = p;
            }
        }
    }
    cout << ans << ' ' << res << '\n';
    for (int i = 0; i < n; ++i) cout << a[i] << (i == n - 1 ? '\n' : ' ');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
