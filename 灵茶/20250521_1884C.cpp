// https://codeforces.com/problemset/problem/1884/C
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

void cf1884C() {
    int n, m;
    cin >> n >> m;
    vector<pii> a;
    for (int i = 0, l, r; i < n; ++i) {
        cin >> l >> r;
        if (l == 1 && r == m) continue;
        a.emplace_back(l, r);
    }
    vector<tiii> b;
    n = a.size();
    for (int i = 0; i < n; ++i) {
        int l = a[i].first, r = a[i].second;
        b.emplace_back(l, 1, i);
        b.emplace_back(r + 1, -1, i);
    }
    sort(b.begin(), b.end());
    int ans = 0, x = 0, y = 0, cur = 0;
    for (auto [pos, val, id] : b) {
        if (val == 1) {
            if (a[id].first == 1) ++x;
            if (a[id].second == m) ++y;
            ++cur;
            ans = max(ans, cur - min(x, y));
        }
        else {
            if (a[id].first == 1) --x;
            if (a[id].second == m) --y;
            --cur;
            ans = max(ans, cur - min(x, y));
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) cf1884C();
}