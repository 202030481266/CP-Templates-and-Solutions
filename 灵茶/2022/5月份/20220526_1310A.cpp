#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

int n;
int a[MAXN], b[MAXN], c[MAXN], ids[MAXN];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        c[i] = a[i];
        ids[i] = i;
    }
    for (int i = 1; i <= n; ++i) cin >> b[i];
    sort(c + 1, c + n + 1);
    for (int i = 2; i <= n; ++i) {
        if (c[i] <= c[i - 1]) c[i] = c[i - 1] + 1;
    }
    sort(ids + 1, ids + 1 + n, [&](int i, int j) { return a[i] < a[j]; });
    int p = 1;
    priority_queue<pii> q;
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        while (p <= n && a[ids[p]] <= c[i]) {
            q.emplace(b[ids[p]], a[ids[p]]);
            ++p;
        }
        auto [cost, origin] = q.top();
        q.pop();
        assert(c[i] >= origin);
        ans += 1ll * cost * (c[i] - origin);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}