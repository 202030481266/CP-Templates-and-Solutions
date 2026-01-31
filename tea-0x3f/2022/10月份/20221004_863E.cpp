// Problem: E. Turn Off The TV
// Contest: Codeforces - Educational Codeforces Round 29
// URL: https://codeforces.com/problemset/problem/863/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


void solve() {
    int n;
    cin >> n;
    vector<pii> arr(n);
    vi b;
    for (auto& p : arr) cin >> p.first >> p.second;
    for (auto& p : arr) {
        b.push_back(p.first);
        b.push_back(p.second);
        b.push_back(p.second + 1);
    }
    ranges::sort(b);
    b.erase(unique(b.begin(), b.end()), b.end());
    vi sum(b.size() + 1);
    for (auto& p : arr) {
        p.first = lower_bound(b.begin(), b.end(), p.first) - b.begin();
        int r = lower_bound(b.begin(), b.end(), p.second + 1) - b.begin();
        p.second = lower_bound(b.begin(), b.end(), p.second) - b.begin();
        ++sum[p.first];
        --sum[r];
    }
    vi c(sum.size());
    int cur = 0;
    for (int i = 0; i < b.size(); ++i) {
        cur += sum[i];
        c[i] = cur;
    }
    int p = 0;
    vector<pii> valid;
    while (p < b.size()) {
        int i = p + 1;
        while (c[p] > 1 && i < b.size() && c[i] > 1) ++i;
        if (c[p] > 1) valid.emplace_back(p, i - 1);
        p = i;
    }
    vi ids(n);
    iota(ids.begin(), ids.end(), 0);
    ranges::sort(ids, [&](int i, int j){
        return arr[i] < arr[j];
    });
    p = 0;
    for (int i = 0; i < valid.size() && p < n; ++i) {
        while (p < n && arr[ids[p]].first < valid[i].first) ++p;
        while (p < n && arr[ids[p]].first <= valid[i].second) {
            if (arr[ids[p]].second <= valid[i].second) {
                cout << ids[p] + 1 << '\n';
                return;
            }
            ++p;
        }
    }
    cout << -1 << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}