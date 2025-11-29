#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 300003;

int n, arr[MAXN];
int b[MAXN], dp[MAXN][6], pre[MAXN][6];

void validate() {
    for (int i = 1; i <= n; ++i) {
        if (b[i] < 1 || b[i] > 5) {
            cout << "Wrong Answer" << '\n';
            return;
        }
        if (i + 1 <= n) {
            if (arr[i] < arr[i + 1]) {
                if (b[i] >= b[i + 1]) {
                    cout << "Wrong Answer" << '\n';
                    return;
                }
            }
            else if (arr[i] > arr[i + 1]) {
                if (b[i] <= b[i + 1]) {
                    cout << "Wrong Answer" << '\n';
                    return;
                }
            }
            else {
                if (b[i] == b[i + 1]) {
                    cout << "Wrong Answer" << '\n';
                    return;
                }
            }
        }
    }
    cout << "Accepted" << '\n';
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= 5; ++i) dp[1][i] = 1;
    for (int i = 2; i <= n; ++i) {
        if (arr[i] > arr[i - 1]) {
            for (int j = 2; j <= 5; ++j) {
                if (dp[i][j - 1]) {
                    pre[i][j] = pre[i][j - 1];
                    dp[i][j] = 1;
                }
                else if (dp[i - 1][j - 1]) {
                    pre[i][j] = j - 1;
                    dp[i][j] = 1;
                }
            }
        }
        else if (arr[i] < arr[i - 1]) {
            for (int j = 4; j >= 1; --j) {
                if (dp[i][j + 1]) {
                    pre[i][j] = pre[i][j + 1];
                    dp[i][j] = 1;
                }
                else if (dp[i - 1][j + 1]) {
                    pre[i][j] = j + 1;
                    dp[i][j] = 1;
                }
            }
        }
        else {
            for (int j = 1; j <= 5; ++j) {
                for (int k = 1; k <= 5; ++k) {
                    if (j == k || !dp[i - 1][k]) continue;
                    dp[i][j] = 1;
                    pre[i][j] = k;
                    break;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= 5; ++i) {
        if (dp[n][i]) ans = i;
    }
    if (!ans) {
        cout << -1 << '\n';
        return;
    }
    for (int i = n, num = ans; i >= 1; --i) {
        b[i] = num;
        num = pre[i][num];
    }
    for (int i = 1; i <= n; ++i) cout << b[i] << (i == n ? '\n' : ' ');
    // validate();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
}
