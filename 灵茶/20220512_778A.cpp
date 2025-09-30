#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    int l = -1, r = n;
    vector<int> can(n, 1);
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        cin >> pos[i];
        --pos[i];
    }
    auto check = [&](int x) -> bool {
        for (int i = 0; i < x; ++i) can[pos[i]] = 0;
        int j = 0;
        for (int i = 0; i < n && j < m; ++i) {
            if (!can[i]) continue;
            if (s[i] == t[j]) ++j;
        }
        for (int i = 0; i < x; ++i) can[pos[i]] = 1;
        return j == m;
    };
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    cout << l << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}