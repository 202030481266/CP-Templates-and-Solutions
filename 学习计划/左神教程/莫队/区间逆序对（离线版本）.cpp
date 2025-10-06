#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int MAXN = 100000 + 5;
static constexpr int MAXE = 200005;

int n, m, arr[MAXN];
int bl[MAXN], br[MAXN], belong[MAXN];
int head[2][MAXN + 5];
int nxt[2][MAXE], to_l[2][MAXE], to_r[2][MAXE], to_qid[2][MAXE], to_op[2][MAXE], tot[2];
int b[MAXN], N;
ll pre[MAXN], suf[MAXN], ans[MAXN];
ll fenwick[MAXN];
ll blockCnt[MAXN], numCnt[MAXN];

inline int lowbit(int i) {
    return i & -i;
}

void update(int p, ll val) {
    while (p <= N) {
        fenwick[p] += val;
        p += lowbit(p);
    }
}

ll query(int p) {
    ll res = 0;
    while (p) {
        res += fenwick[p];
        p -= lowbit(p);
    }
    return res;
}

void addLeft(int val) {
    for (int i = 1; i < belong[val]; ++i) ++blockCnt[i];
    for (int i = bl[belong[val]]; i < val; ++i) ++numCnt[i];
}

void addRight(int val) {
    for (int i = belong[val] + 1; i <= belong[N]; ++i) ++blockCnt[i];
    for (int i = val + 1; i <= br[belong[val]]; ++i) ++numCnt[i];
}

struct Query {
    int l, r, id;
    Query(): l(0), r(0), id(0) {}
    Query(int _l, int _r, int _id): l(_l), r(_r), id(_id) {}
    bool operator<(const Query& q) const {
        if (belong[l] != belong[q.l]) return belong[l] < belong[q.l];
        return r < q.r;
    }
} qs[MAXN];

void addEdge(int idx, int u, int ql, int qr, int qid, int qop) {
    ++tot[idx];
    to_l[idx][tot[idx]] = ql;
    to_r[idx][tot[idx]] = qr;
    to_qid[idx][tot[idx]] = qid;
    to_op[idx][tot[idx]] = qop;
    nxt[idx][tot[idx]] = head[idx][u];
    head[idx][u] = tot[idx];
}

void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        b[i] = arr[i];
    }
    sort(b + 1, b + n + 1);
    N = static_cast<int>(unique(b + 1, b + n + 1) - b - 1);
    for (int i = 1; i <= n; ++i) {
        arr[i] = static_cast<int>(lower_bound(b + 1, b + N + 1, arr[i]) - b);
    }
    for (int i = 1, l, r; i <= m; ++i) {
        cin >> l >> r;
        qs[i] = Query(l, r, i);
    }
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + query(N) - query(arr[i]);
        update(arr[i], 1);
    }
    memset(fenwick, 0, sizeof(fenwick));
    for (int i = n; i >= 1; --i) {
        suf[i] = suf[i + 1] + query(arr[i] - 1);
        update(arr[i], 1);
    }
    int blen = max(1, static_cast<int>(sqrt(n)));
    int bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= n; ++i) belong[i] = (i - 1) / blen + 1;
    for (int i = 1; i <= bnum; ++i) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(i * blen, N);
    }
    sort(qs + 1, qs + 1 + m);
    for (int i = 1, l = 1, r = 0; i <= m; ++i) {
        int ql = qs[i].l, qr = qs[i].r, qid = qs[i].id;
        if (r < qr) {
            addEdge(0, l - 1, r + 1, qr, qid, -1);
            ans[qid] += pre[qr] - pre[r];
        }
        if (r > qr) {
            addEdge(0, l - 1, qr + 1, r, qid, 1);
            ans[qid] -= pre[r] - pre[qr];
        }
        r = qr;
        if (l > ql) {
            addEdge(1, r + 1, ql, l - 1, qid, -1);
            ans[qid] += suf[ql] - suf[l];
        }
        if (l < ql) {
            addEdge(1, r + 1, l, ql - 1, qid, 1);
            ans[qid] -= suf[l] - suf[ql];
        }
        l = ql;
    }
    for (int i = 0; i <= n; ++i) {
        if (i >= 1) addLeft(arr[i]);
        for (int x = head[0][i]; x; x = nxt[0][x]) {
            for (int j = to_l[0][x]; j <= to_r[0][x]; ++j) {
                ans[to_qid[0][x]] += (blockCnt[belong[arr[j]]] + numCnt[arr[j]]) * to_op[0][x];
            }
        }
    }
    memset(blockCnt, 0, sizeof(blockCnt));
    memset(numCnt, 0, sizeof(numCnt));
    for (int i = n + 1; i >= 1; --i) {
        if (i <= n) addRight(arr[i]);
        for (int x = head[1][i]; x; x = nxt[1][x]) {
            for (int j = to_l[1][x]; j <= to_r[1][x]; ++j) {
                ans[to_qid[1][x]] += (blockCnt[belong[arr[j]]] + numCnt[arr[j]]) * to_op[1][x];
            }
        }
    }
    for (int i = 2; i <= m; ++i) {
        ans[qs[i].id] += ans[qs[i - 1].id];
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}

int main() {
    solve();
    return 0;
}