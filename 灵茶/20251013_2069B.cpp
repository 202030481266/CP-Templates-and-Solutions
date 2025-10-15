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

int n, m;
int grid[702][702];
int color[MAXN], cnt[MAXN];

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
            color[grid[i][j]] = 0;
            cnt[grid[i][j]] = 0;
        }
    }
    int sum = 0, tot = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ++cnt[grid[i][j]];
            if (cnt[grid[i][j]] == 1) ++tot;
            if (color[grid[i][j]]) continue;
            if (grid[i][j] == grid[i - 1][j] || grid[i][j] == grid[i][j - 1]) {
                color[grid[i][j]] = 1;
                ++sum;
            }
        }
    }
    // tot - sum + (sum - 1) * 2 = tot + sum - 2
    if (tot == 1) cout << 0 << '\n';
    else if (sum) cout << tot + sum - 2 << '\n';
    else cout << tot - 1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
