#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 200005;

int fa[maxn], mn[maxn], mx[maxn];
int n, m;
array<int, 3> arr[maxn];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y, int w) {
    int fx = find(x), fy = find(y);
    fa[fy] = fx;
    mn[fx] = min(mn[fx], min(w, mn[fy]));
    mx[fx] = max(mx[fx], max(w, mx[fy]));
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        mn[i] = inf;
        mx[i] = 0;
        fa[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        cin >> arr[i][1] >> arr[i][2] >> arr[i][0]; // w, u, v
    }
    sort(arr + 1, arr + m + 1);
    int ans = inf * 2;
    for (int i = 1; i <= m; ++i) {
        int u = arr[i][1], v = arr[i][2], w = arr[i][0];
        merge(u, v, w);
        if (find(1) == find(n)) {
            int f = find(n);
            ans = min(ans, mx[f] + mn[f]);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
	cin >> t;
    while (t--) solve();
    return 0;
}