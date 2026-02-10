#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int vis[1 << 20];

void solve() {
    int n, k;
    cin >> n >> k;
    vi arr(n);
    for (int i = 0; i < n; ++i) {
        char ch;
        cin >> ch;
        arr[i] = (ch - '0') ^ 1;
    }
    int w = bit_width(1u * (n - k + 1));
    w = min(w, k);
    int l = k - w, cur = 0;
    vi res;
    int sum = 0, p = 0;
    for (int i = 0; i < k - w; ++i) sum += arr[i];
    for (int i = k - w; i < n; ++i) {
        cur = (cur << 1) + arr[i];
        if (i - l + 1 > w) {
            sum -= arr[p++];
            sum += arr[l++];
            cur &= ~(1 << w);
        }
        if (i - l + 1 == w && (k == w || sum == 0)) {
            res.push_back(cur);
            vis[cur] = 1;
        }
    }
    int ans = -1;
    for (int i = 0; i < 1 << w; ++i) {
        if (!vis[i]) {
            ans = i;
            break;
        }
    }
    for (int v : res) vis[v] = 0;
    if (ans == -1) cout << "NO\n";
    else {
        cout << "YES\n";
        for (int i = 0; i < k - w; ++i) cout << '0';
        for (int i = w - 1; i >= 0; --i) cout << (ans >> i & 1);
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}