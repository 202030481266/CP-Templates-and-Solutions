// Problem: D. Fedor and coupons
// Contest: Codeforces - Codeforces Round 390 (Div. 2)
// URL: https://codeforces.com/problemset/problem/754/D
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
static constexpr int MAXN = 300005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

inline int lowbit(int i) {
    return i & -i;
}
int n, k;
int fenwick[MAXN * 3], b[MAXN * 3], N = 0, use[MAXN];
int head[MAXN * 3], nxt[MAXN * 3], to[MAXN * 3], type[MAXN * 3], tot = 0;
pii arr[MAXN];

void update(int p, int val) {
    while (p <= N) {
        fenwick[p] += val;
        p += lowbit(p);
    }
}

int kth(int S) {
    int pos = 0, acc = 0, mask = 1;
    while ((mask << 1) <= N) mask <<= 1;
    for (int k = mask; k > 0; k >>= 1) {
        if (pos + k <= N && acc + fenwick[pos + k] < S) {
            acc += fenwick[pos + k];
            pos += k;
        }
    }
    return pos + 1;
}

void addEdge(int u, int v, int w) {
    to[++tot] = v;
    type[tot] = w;
    nxt[tot] = head[u];
    head[u] = tot;
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> arr[i].first >> arr[i].second;
    for (int i = 1; i <= n; ++i) {
        b[++N] = arr[i].first;
        b[++N] = arr[i].second;
        b[++N] = arr[i].second + 1;
    }
    sort(b + 1, b + 1 + N);
    N = unique(b + 1, b + 1 + N) - b - 1;
    for (int i = 1, r; i <= n; ++i) {
        r = lower_bound(b + 1, b + 1 + N, arr[i].second + 1) - b;
        arr[i].first = lower_bound(b + 1, b + 1 + N, arr[i].first) - b;
        arr[i].second = lower_bound(b + 1, b + 1 + N, arr[i].second) - b;
        addEdge(arr[i].first, i, 1);
        addEdge(r, i, -1);
    }
    int cur = 0, p = -1, mx = 0, st = -1; 
    for (int i = 1; i <= N; ++i) {
        for (int j = head[i]; j; j = nxt[j]) {
            cur += type[j];
            update(arr[to[j]].first, type[j]);
        }
        if (cur >= k) {
            int j = kth(k);
            if (mx < b[i] - b[j] + 1) {
                mx = b[i] - b[j] + 1;
                p = i;
                st = j;
            }
        }
    }
    cout << mx << '\n';
    if (mx == 0) {
        for (int i = 1; i <= k; ++i) cout << i << ' ';
    }
    else {
        for (int i = 1; i <= p; ++i) {
            for (int j = head[i]; j; j = nxt[j]) {
                if (type[j] == -1) use[to[j]] = 0;
                else use[to[j]] = 1;
            }
        }
        for (int i = 1, x = 0; x < k && i <= n; ++i) {
            if (use[i] && arr[i].first <= st) {
                ++x;
                cout << i << ' ';
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}