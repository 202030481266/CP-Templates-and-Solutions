#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int INF = 0x3f3f3f3f;

int n, m;
int ans[MAXN], qs[MAXN][3], cnt[MAXN], sum[MAXN];

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> qs[i][0] >> qs[i][1] >> qs[i][2];
    }
    for (int i = 0; i < 30; ++i) {
        memset(cnt, 0, (n + 1) * sizeof(int));
        for (int j = 1; j <= m; ++j) {
            if (qs[j][2] >> i & 1) {
                cnt[qs[j][0]]++;
                cnt[qs[j][1] + 1]--;
            }
        }
        for (int j = 1; j <= n; ++j) {
            cnt[j] += cnt[j - 1];
            sum[j] = sum[j - 1] + (cnt[j] > 0 ? 1 : 0);
            if (cnt[j] > 0) ans[j] |= 1 << i;
        }
        for (int j = 1; j <= m; ++j) {
            if ((qs[j][2] >> i & 1) == 0) {
                if (sum[qs[j][1]] - sum[qs[j][0] - 1] == qs[j][1] - qs[j][0] + 1) {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }
    cout << "YES\n";
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
}

