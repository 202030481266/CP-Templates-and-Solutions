// Problem: E. Segments Removal
// Contest: Codeforces - Codeforces Round 452 (Div. 2)
// URL: https://codeforces.com/problemset/problem/899/E
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

int n, arr[MAXN], nxt[MAXN], pre[MAXN];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    int p = 1;
    nxt[n + 1] = n + 1;
    nxt[0] = 1;
    pre[1] = 0;
    set<pii> s;
    vi cnt(n + 1);
    while (p <= n) {
        int i = p + 1;
        while (i <= n && arr[i] == arr[p]) ++i;
        nxt[p] = i;
        pre[i] = p;
        cnt[p] = i - p;
        s.emplace(cnt[p], -p);
        p = i;
    }
    int ans = 0;
    while (!s.empty()) {
        ++ans;
        auto [_, i] = *s.rbegin();
        s.erase(prev(s.end()));
        i *= -1;
        if (pre[i] >= 1 && nxt[i] <= n && arr[pre[i]] == arr[nxt[i]]) {
            s.erase(s.find({cnt[pre[i]], -pre[i]}));
            s.erase(s.find({cnt[nxt[i]], -nxt[i]}));
            cnt[pre[i]] += cnt[nxt[i]];
            nxt[pre[i]] = nxt[nxt[i]];
            pre[nxt[nxt[i]]] = pre[i];
            s.emplace(cnt[pre[i]], -pre[i]);
        }
        else {
            nxt[pre[i]] = nxt[i];
            pre[nxt[i]] = pre[i];
        }
    }
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}