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

ll arr[MAXN];

void solve() {
    int m, op, tot = 0, p = 0;
    ll sum = 0;
    double ans = 0;
    cin >> m;
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> arr[tot];
            while (p < tot && arr[p] * (p + 1) <= arr[tot] + sum) sum += arr[p++];
            ans = max(ans, arr[tot] * 1.0 - 1.0 * (arr[tot] + sum) / (p + 1)); // [0, p)
            ++tot;
        }
        else cout << fixed << setprecision(8) << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
