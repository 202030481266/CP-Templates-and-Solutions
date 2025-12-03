#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using t4i = tuple<int, int, int, int>;

static constexpr int MAXN = 105;

int dp[MAXN][MAXN][MAXN];
t4i pre[MAXN][MAXN][MAXN];

string a, b, t;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a >> b >> t;
    int n = a.size(), m = b.size(), sz = t.size();
    // kmp
    vector<int> nxt(sz);
    for (int i = 1, j = 0; i < sz; ++i) {
        while (j > 0 && t[i] != t[j]) j = nxt[j - 1];
        if (t[i] == t[j]) ++j;
        nxt[i] = j;
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k < sz; ++k) {
                if (dp[i + 1][j][k] < dp[i][j][k]) {
                    dp[i + 1][j][k] = dp[i][j][k];
                    pre[i + 1][j][k] = {i, j, k, 0};
                }
                if (dp[i][j + 1][k] < dp[i][j][k]) {
                    dp[i][j + 1][k] = dp[i][j][k];
                    pre[i][j + 1][k] = {i, j, k, 0};
                }
                if (i + 1 <= n && j + 1 <= m && a[i] == b[j]) {
                    int p = k;
                    while (p > 0 && a[i] != t[p]) p = nxt[p - 1];
                    if (a[i] == t[p]) ++p;
                    if (dp[i + 1][j + 1][p] < dp[i][j][k] + 1) {
                        dp[i + 1][j + 1][p] = dp[i][j][k] + 1;
                        pre[i + 1][j + 1][p] = {i, j, k, 1};
                    }
                }
            }
        }
    }
    int ans = 0;
    t4i cur;
    for (int i = 0; i < sz; ++i) {
        if (dp[n][m][i] > ans) {
            ans = dp[n][m][i];
            cur = {n, m, i, 0};
        }
    }
    if (ans == 0) {
        cout << ans << '\n';
    } else {
        string lcs;
        while (true) {
            auto [i, j, k, _] = cur;
            if (i <= 0 || j <= 0) break;
            if (get<3>(pre[i][j][k])) lcs.push_back(a[i - 1]);
            cur = pre[i][j][k];
        }
        reverse(lcs.begin(), lcs.end());
        cout << lcs << '\n';
    }
}