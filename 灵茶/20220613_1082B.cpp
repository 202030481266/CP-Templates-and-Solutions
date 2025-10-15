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

void solve() {
    int n;
    cin >> n;
    vector<char> s(n);
    for (char &c : s) cin >> c;
    int p = 0, ans = 0;
    vector<pii> arr;
    while (p < n) {
        int i = p + 1;
        while (i < n && s[i] == s[p]) ++i;
        if (s[p] == 'G') {
            ans = max(ans, i - p);
            arr.emplace_back(p, i);
        }
        p = i;
    }
    if (arr.size() <= 1) {
        cout << ans << '\n';
        return;
    }
    int m = arr.size();
    for (int i = 0; i < m; ++i) {
        ans = max(ans, arr[i].second - arr[i].first + 1);
        if (i > 0 && arr[i - 1].second + 1 == arr[i].first) {
            int tot = arr[i].second - arr[i].first + arr[i - 1].second - arr[i - 1].first;
            if (m == 2) ans = max(ans, tot);
            else ans = max(ans, tot + 1);
        }
    }
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
