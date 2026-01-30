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
    int person = 0;
    vi cnt(n + 1); 
    vi pos(n + 1);
    for (int i = 1; i <= n; ++i) {
        cnt[i] = cnt[i - 1];
        if (arr[i]) pos[++person] = i;
        else ++cnt[i];
    }
    vii dp(n + 1, vi(n + 1, INF));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= min(person, cnt[i]); ++j) {
            dp[i][j] = dp[i - 1][j];
            if (!arr[i] && j) dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + abs(pos[j] - i));
        }
    }
    cout << dp[n][person] << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
