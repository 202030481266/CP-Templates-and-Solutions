#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int INF = 0x3f3f3f3f;

int n, k;
char s[MAXN];

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> s[i];
    int res = 0;
    for (int i = 1; i < min(n, k); ++i) {
        int x = 0, y = res + 1;
        while (y <= i && s[x] == s[y]) {
            x = (x + 1) % (res + 1);
            ++y;
        }
        if (y <= i && s[y] < s[x]) res = i;
    }
    for (int i = 0, j = 0; j < k; i = (i + 1) % (res + 1), ++j) cout << s[i];
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
}
