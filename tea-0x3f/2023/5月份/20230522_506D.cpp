// Problem: D. Mr. Kitayuta's Colorful Graph
// Contest: Codeforces - Codeforces Round 286 (Div. 1)
// URL: https://codeforces.com/contest/506/problem/D
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 100005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int fa[MAXN];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int fast[200][MAXN];

void solve() {
    int n, m, q;
    cin >> n >> m;
    vii have(n + 1);
    vector edges(m + 1, vector<pii>{});
    for (int i = 0, u, v, c; i < m; ++i) {
        cin >> u >> v >> c;
        have[u].push_back(c);
        have[v].push_back(c);
        edges[c].emplace_back(u, v);
    }
    int N = static_cast<int>(sqrt(2 * m)); // fix 1
    vi big;
    vi idx(n + 1);
    vi isBig(n + 1);
    vii color(m + 1);
    for (int i = 1; i <= n; ++i) {
        auto& arr = have[i];
        ranges::sort(arr);
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        if (arr.size() >= N) {
            idx[i] = big.size();
            big.push_back(i);
            isBig[i] = 1;
            for (int c : arr) {
                color[c].push_back(i);
                fast[idx[i]][c] = 1;
            }
        }
    }
    vector cnt(big.size(), vector(big.size(), vi{}));
    for (int i = 1; i <= m; ++i) {
        if (color[i].size() < 2) continue;
        auto& arr = color[i];
        int sz = arr.size();
        for (int x = 0; x < sz; ++x) {
            for (int y = x + 1; y < sz; ++y) {
                cnt[idx[arr[x]]][idx[arr[y]]].push_back(i); // fix 2
            }
        }
    }
    cin >> q;
    vi ans(q);
    vi con(m + 1);
    vector g(m + 1, vector<tuple<int, int, int>>{});
    vector<tuple<int, int, int>> qs;
    for (int i = 0, u, v; i < q; ++i) {
        cin >> u >> v;
        if (u > v) swap(u, v);
        qs.emplace_back(u, v, i);
    }
    ranges::sort(qs);
    int p = 0;
    while (p < q) {
        int i = p + 1;
        while (i < q && get<0>(qs[p]) == get<0>(qs[i]) && get<1>(qs[p]) == get<1>(qs[i])) ++i;
        auto [u, v, qid] = qs[p];
        if (have[u].size() < have[v].size()) swap(u, v);
        if (isBig[u]) {
            if (isBig[v]) {
                if (u > v) swap(u, v);
                for (int c : cnt[idx[u]][idx[v]]) g[c].emplace_back(u, v, qid);
            }
            else {
                for (int c : have[v]) { // fix 3
                    if (fast[idx[u]][c]) g[c].emplace_back(u, v, qid);
                }
            }
        }
        else {
            for (int c : have[u]) con[c] = 1;
            for (int c : have[v]) {
                if (con[c]) {
                    con[c] = 0;
                    g[c].emplace_back(u, v, qid);
                }
            }
            for (int c : have[u]) con[c] = 0;
        }
        p = i;
    }
    for (int i = 1; i <= m; ++i) {
        if (g[i].empty() || edges[i].empty()) continue;
        for (auto [u, v] : edges[i]) {
            fa[u] = u;
            fa[v] = v;
        }
        for (auto [u, v] : edges[i]) {
            int fu = find(u);
            int fv = find(v);
            if (fu != fv) fa[fu] = fv;
        }
        for (auto [u, v, qid] : g[i]) {
            int fu = find(u);
            int fv = find(v);
            if (fu == fv) ++ans[qid];
        }
    }
    p = 0;
    while (p < q) {
        int i = p + 1;
        while (i < q && get<0>(qs[p]) == get<0>(qs[i]) && get<1>(qs[p]) == get<1>(qs[i])) ++i;
        for (int j = p + 1; j < i; ++j) {
            ans[get<2>(qs[j])] = ans[get<2>(qs[p])];
        }
        p = i;
    }
    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}