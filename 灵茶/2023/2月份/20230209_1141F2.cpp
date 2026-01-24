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
    vl sum(n + 1);
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + arr[i];
    vector<pair<ll, int>> b;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            ll s = sum[i] - sum[j];
            b.emplace_back(s, (i - 1) * n + j);
        }
    }
    ranges::sort(b);
    int m = b.size();
    int p = 0;
    int ans = 0;
    vector<pii> solution;
    while (p < m) {
        int q = p + 1;
        while (q < m && b[q].first == b[p].first) ++q;
        vector<pii> interval;
        vi res{0};
        for (int i = p; i < q; ++i) {
            interval.emplace_back(b[i].second % n, b[i].second / n + 1);
        }
        ranges::sort(interval, [&](const pii& a, const pii& b) {
            return a.second < b.second;
        });
        int cnt = 1, ed = interval[0].second;
        for (int i = 1; i < (int)interval.size(); ++i) {
            if (interval[i].first >= ed) {
                ++cnt;
                res.push_back(i);
                ed = interval[i].second;
            }
        }
        if (cnt > ans) {
            ans = cnt;
            solution.clear();
            for (int idx : res) solution.emplace_back(interval[idx]);
        }
        p = q;
    }
    cout << ans << '\n';
    for (auto [l, r] : solution) {
        cout << l + 1 << ' ' << r << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
